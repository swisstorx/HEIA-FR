#!/bin/bash
#
# A program to demonstrate while and until loops
#

nloops=3
i=0

echo "while loop"
while [[ $i<$nloops ]]; do
    echo $i
    let i++
done

echo
echo "until loop"
i=0
until [[ $i>$nloops ]]; do
    echo $i
    let i++
done
