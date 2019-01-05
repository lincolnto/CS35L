#!/bin/sh
while read p; do
    echo "$p"
    ldd "/usr/bin/$p"
done < commands.txt
