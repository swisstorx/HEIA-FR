#!/bin/bash
#
# A program to demonstrate the use of a type 1 for loop.
#

word="a b c"
i=0

# Read each character from $word and and asign it to $name
for name in $word; do

    # Use 'let' to increment i.
    let i++

    # Print the value of $name
    echo $name

done

echo "Looped $i times."
