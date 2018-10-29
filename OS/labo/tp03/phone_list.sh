#!/bin/bash

input="collaborateurs.csv"
while read line; do
    phone=$(echo $line | cut -d \; -f 3)
    if [ -n "$phone" ]; then
        firstname=$(echo $line | cut -d \; -f 2)
        name=$(echo $line | cut -d \; -f 1)
        echo "${firstname} ${name} -> ${phone}"
    fi
done < ${input}
