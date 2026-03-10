#!/bin/sh
# Assignment 1 Finder Script. Searches files under the specified directory for
# the given string.

# Usage: finder.sh <filesdir> <searchstr>

# Verify exactly two arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

# Verify that the specified directory exists
if [ ! -d "$1" ]; then
    echo "Failure: Directory $1 does not exist."
    exit 1
fi

# Set args to variables
filesdir="$1"
searchstr="$2"

# Use find to get a count of all files in the target and subdirecto4ries
FILECOUNT=$(find "$filesdir" -type f | wc -l)

# Recursive grep through files for our searchstr
LINECOUNT=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Finally, print results.
echo "The number of files are ${FILECOUNT} and the number of matching lines are ${LINECOUNT}"