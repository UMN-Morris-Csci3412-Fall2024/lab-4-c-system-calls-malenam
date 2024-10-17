#!/bin/bash

# Check if the number of arguments is exactly 1
if [ "$#" -ne 1 ]; then
    # Print usage information if the argument count is incorrect
    echo "Usage: $0 <path>"
    echo "       where <path> is the file or root of the tree you want to summarize."
    exit 1  # Exit with an error code
fi

# Assign the first argument to the variable 'path'
path=$1

# Count the number of directories in the given path
num_dirs=$(find "$path" -type d | wc -l)
# Count the number of regular files in the given path
num_regular=$(find "$path" -type f | wc -l)

# Print the results
echo "Processed all the files from $path."
echo "There were $num_dirs directories."
echo "There were $num_regular regular files."