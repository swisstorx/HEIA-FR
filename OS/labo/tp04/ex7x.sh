#!/bin/bash
#
# A program to demonstrate the use of conditional string operators.
#

if [[ -n $CHECK_ME ]]; then
    echo "CHECK_ME = $CHECK_ME"
else
    echo "CHECK_ME is unset."
fi
