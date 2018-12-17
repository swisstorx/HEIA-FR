#!/bin/bash
#
# A program to that uses conditional expressions to test for
# the presence of a file.
#

files="test test_dir test_link"
# Try replacing $files with `ls`. This will cause the ls command to be run
# and the output to be used for the tests.

for file in $files; do
    if [[ -a $file ]]; then
        echo "File $file Exists"
    fi

    if [[ -f $file ]]; then
        echo "File $file is a regular file"
    fi

    if [[ -d $file ]]; then
        echo "File $file is a directory"
    fi

    if [[ -h $file ]]; then
        echo "File $file is a symbolic link"
    fi
done

