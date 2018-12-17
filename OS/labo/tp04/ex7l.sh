#!/bin/bash
#
# A script to remove part of a string using Parameter Expansion.
#

parameter="filename.dat"
lastword=".dat"
firstword="file"

remainder1=${parameter%$lastword}
remainder2=${parameter#$firstword}

echo "parameter=$parameter"
echo "firstword=$firstword"
echo "lastword=$lastword"
echo "remainder1=$remainder1"
echo "remainder2=$remainder2"
