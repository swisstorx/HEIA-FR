#!/bin/bash
#
# A program to demonstrate the use of a type 2 for loop.
#

# Loop from 0 to 9.
for((i=0; i<10; i++)) ; do

    # Append the string form of i to the end of the string j
    j=$j$i

done

echo $j
