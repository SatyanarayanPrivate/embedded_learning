#!/bin/bash

# Check for number of arguments
if [ $# -ne 2 ]; then
    echo "Usage: test.sh num1 num2"
    exit 0
fi

if [ "$1" -eq "$1" ] &&  [ "$2" -eq "$2" ]; then
    echo "$1 + $2:`expr $1 + $2`"
else
    echo "Please Enter Integer number's"
    exit 0
fi
