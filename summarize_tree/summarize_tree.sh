#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path>"
    echo "       where <path> is the file or root of the tree you want to summarize."
    exit 1
fi

path=$1

num_dirs=$(find "$path" -type d | wc -l)
num_regular=$(find "$path" -type f | wc -l)

echo "Processed all the files from $path."
echo "There were $num_dirs directories."
echo "There were $num_regular regular files."