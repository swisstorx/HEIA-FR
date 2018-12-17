#!/bin/bash
#
# A program to demonstrate file i/o using output redirection.
#

words="electron muon tau"
outputfile="test.out"

# Remove the output file if it already exists
rm -f $outputfile

# Fill the output file with the words
for name in $words; do
    echo $name >> $outputfile
done

# Use cat to print the contents of the output file
echo "cat $outputfile:"
cat $outputfile

echo
echo "Reading the words back in."
for name in $(<$outputfile); do
    str="$str$name, "
done
echo $str

