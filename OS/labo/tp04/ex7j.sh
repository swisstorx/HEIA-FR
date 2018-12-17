#!/bin/bash
#
# A simple program to illustrating how command line arguments can be read
# inside a shell program.
#

echo "The number of arguments following the command = $#";

for arg in $* ; do
    str="$str $arg"
done

echo "$0"
echo "$0$str"
