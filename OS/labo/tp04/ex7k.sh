#!/bin/bash
#
# A script demonstrating substring selection via Parameter Expansion
#

somestring=abcdef

echo ${somestring}
echo "length = ${#somestring}"

i=2
echo "After $i characters ${somestring:$i}"
echo "Before $i characters ${somestring: -$i}"

j=2
echo "From char $i for length $j ${somestring:$i:$j}"
