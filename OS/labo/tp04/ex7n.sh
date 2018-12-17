#!/bin/bash
#
# A script demonstrating string pattern matching.
# Note the escaped (\) double quotes in the echo statement.
# this means the quotes will be printed as quotes, and not treated as the
# end of the echo statement.
#

filename1="string"
filename2="xyzstringxyz"
match="xyzstring"

if [[ "$filename2" == *"$filename1"* ]]; then
    echo "*\"$filename1\"* matches \"$filename2\" "
fi
if [[ "$filename2" == "$match"* ]]; then
    echo "\"$match\"* matches \"$filename2\""
fi
