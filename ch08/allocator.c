#define _DEFAULT_SOURCE
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEADER_ALIGNMENT_TYPE max_align_t
#define HEADER_ALIGNMENT alignof(HEADER_ALIGNMENT_TYPE)

void write_int_to_stderr(int n) {
  char buf[20]; // enough to hold a 64-bit int with sign
  int i = 0;
  int is_negative = 0;

  if (n == 0) {
    write(2, "0", 1);
    return;
  }

  if (n < 0) {
    is_negative = 1;
    // handle INT_MIN edge case
    if (n == -2147483648) {
      write(2, "-2147483648", 11);
      return;
    }
    n = -n;
  }

  // Convert number to string in reverse
  while (n > 0) {
    buf[i++] = '0' + (n % 10);
    n /= 10;
  }

  if (is_negative)
    buf[i++] = '-';

  // Write the string in correct order
  while (i--)
    write(2, &buf[i], 1);
}

typedef struct header {
  struct header *next;
  size_t size;

  // NOTE: This is a zero byte field that servers two purposes:
  // 1. It forces the alignment of the header to the maximum value so callers
  //    get a starting address that is aligned to whatever type they use.
  // 2. Using a FAM allows us to easily reference the memory after the header
  //    which is where the requested allocated memory starts. Obviously use with
  //    caution as dealing with characters beyond the header when there are none
  //    could result in chaos.
  alignas(HEADER_ALIGNMENT_TYPE) char start[];
} header;

// NOTE: This asserts that both the size and alignment of the header are equal
// to the max alignment.
static_assert(sizeof(header) == alignof(header));
static_assert(alignof(header) == HEADER_ALIGNMENT);

// NOTE: base is a starting value for the free list.
static header base = {};

// NOTE: freep points to an element of the free list where malloc will start
// looking for free memory.
static header *freep = NULL;

void free(void *ip) {
  auto bp = (header *)ip - 1;

  // find where the free'd memory goes in the free list
  header *p;
  for (p = freep; !(bp > p && bp < p->next); p = p->next) {
    if (p >= p->next && (bp > p || bp < p->next))
      break;
  }

  if (bp + bp->size == p->next) {
    // the memory ahead of this location is contiguous, merge
    bp->size += p->next->size;
    bp->next = p->next->next;
  } else {
    // just point at it
    bp->next = p->next;
  }

  if (p + p->size == bp) {
    // the memory behind this location is contiguous, merge
    p->size += bp->size;
    p->next = bp->next;
  } else {
    // just point at it
    p->next = bp;
  }

  freep = p;
}

#define MIN_UNITS 1024

static header *morecore(size_t units) {
  if (units < MIN_UNITS)
    units = MIN_UNITS;

  // TODO: How do you ensure that this location is aligned propperly? Could sbrk
  // return a pointer to a byte location that is non-aligned?
  // TODO: Apparently sbrk starts aligned to page size but can get unaligned by
  // calls to it that are not aligned.
  auto cp = sbrk(units * sizeof(header));
  if (cp == (void *)-1)
    return NULL;

  auto p = (header *)cp;
  p->size = units;
  free(p + 1);
  return freep;
}

void *malloc(size_t size) {
  // one time init for base/freep
  if (freep == NULL) {
    base.next = &base;
    freep = &base;
  }

  // figure out how many units we need for the requested size
  auto units = (size + sizeof(header) - 1) / sizeof(header) + 1;

  header *p, *prevp;
  prevp = freep;
  p = prevp->next;
  for (;;) {
    // check if this free section is big enough, if so, split it, take the used
    // bytes out of the free list, and return them
    if (p->size >= units) {
      // found a section big enough for requested size
      if (p->size == units) {
        // exact match! remove it from the free list
        prevp->next = p->next;
      } else {
        // it is too big

        // subtract it down to size
        p->size -= units;

        // advance our pointer to point to the newly free'd up space
        p += p->size;

        // make sure our new header has its units set
        // NOTE: The ptr field could probably be set to NULL as well but it
        // isn't needed.
        p->size = units;
      }

      // start where we left off next time malloc is called
      freep = prevp;

      // return the location but one header size off
      return (void *)(p + 1);
    }

    // if we ever wrap around to the start
    if (p == freep) {
      // then request more memory from the os and added to the free list
      p = morecore(units);
      if (p == NULL) {
        return NULL;
      }
    }

    prevp = p;
    p = p->next;
  }

  return NULL;
};

int main(int argc, char *argv[]) {
  for (auto i = 0; i < 35; ++i) {
    fprintf(stderr, "%d: ", i);
    fflush(stderr);
    auto p = malloc(i);
    fprintf(stderr, " p: %p\n", p);
    free(p);
  }

  return EXIT_SUCCESS;
}
