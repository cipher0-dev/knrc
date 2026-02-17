#!/bin/bash
make build/test_int_sizes build/test_int_sizes_32
build/test_int_sizes_32 > /tmp/32
build/test_int_sizes > /tmp/64
delta /tmp/{32,64}
