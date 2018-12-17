#!/bin/bash
#
# A script demonstrating functions
#

#------------ a function called usage()------------------
usage() {
    echo "Usage: No parameters given!"
    exit 1
}
#------------------ end function ------------------------

# Check at least one argument is given
if [[ -z $1 ]]; then
    usage
fi
echo "we have at least one argument"
exit 0
