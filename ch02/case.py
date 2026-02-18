#!/usr/bin/env python

def toggle_case(c):
    return chr(ord(c) ^ ord(' '))

def to_lower(c):
    return chr(ord(c) | ord(' '))

def to_upper(c):
    return chr(ord(c) & ~ord(' '))

assert(toggle_case("W") == "w")
assert(toggle_case("w") == "W")
assert(to_upper("W") == "W")
assert(to_upper("w") == "W")
assert(to_lower("W") == "w")
assert(to_lower("w") == "w")
