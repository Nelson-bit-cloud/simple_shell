#!/bin/bash

# Check if the number of arguments is correct
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <name>"
    exit 1
fi

# Extract the name from the command line argument
name=$1

# Print a greeting message
echo "/bin/echo Holberton" | ./hsh

# Check the current PATH
echo "Current PATH: $PATH"

# Rest of your script goes here
export PATH=/bin:$PATH

# Example command using the updated PATH
/bin/echo Holberton

# End of the script
