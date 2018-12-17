#!/bin/bash
#
# A script demonstrating external commands
#

#run the command with '$()'
result1=$(uptime)

#entirely equivalent.. run with ``
result2=`last | tail -n 1`

echo "result1 ->" $result1
echo "result2 ->" $result2
