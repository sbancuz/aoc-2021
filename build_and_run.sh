#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra -Wshadow -Werror -std=c11 -pedantic -ggdb"

gcc $CFLAGS -o $1 $1.c && ./$1
