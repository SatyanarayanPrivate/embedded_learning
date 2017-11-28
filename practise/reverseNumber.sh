#!/bin/bash


num=$1
rev=0

while (( num > 0 )); do
    
    rev=$(( num % 10 + rev * 10 ))
    let num/=10
done

echo "reverse of $1 is $rev" 
