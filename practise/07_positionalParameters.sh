#!/bin/bash

# Posotional parameters
# allows only 0-9 
# 0: execution file
<<COMMENT
    All command line parameters or arguments can be accessed via $1, $2, $3,..., $9.
    $* holds all command line parameters or arguments, seperated by value of $IFS.
    $# holds the number of positional parameters.
    $- holds flags supplied to the shell.
    $? holds the return value set by the previously executed command.
    $$ holds the process number of the shell (current shell).
    $! hold the process number of the last background command.
    $@ holds all command line parameters or arguments.
COMMENT
sum=0

while [ $# -gt 0 ]; do
    num=$1
    sum=$((sum + num))
    shift   # will move command line arguments by one
done

echo "Sum: $sum"
