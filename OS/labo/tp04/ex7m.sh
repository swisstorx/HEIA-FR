#!/bin/bash
#
# A script to replace part of a string using Parameter Expansion
#

parameter="filename.dat"
pattern=".dat"
string=".root"

new_filename=${parameter/$pattern/$string}
echo "parameter=$parameter pattern=$pattern string=$string"
echo "new_filename=$new_filename"
