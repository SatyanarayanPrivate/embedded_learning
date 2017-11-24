#!/bin/bash

# Functions 

# Simple function calling
getDate(){
    date
    return 
}

getDate
echo "-----------------------------------------------"

# Globle and local variable"

varTest1="Globle Var1"
varTest2="Globle Var2"
demoLocal(){
    local varTest1="Local Var1"
    varTest3="Test3"  # it will consider as global variable
    echo "varTest1: $varTest1"
    echo "varTest2: $varTest2"
    echo "varTest3: $varTest3"
    
    varTest2="Var2 Value Changed"
    return
}

demoLocal

echo "varTest1: $varTest1"
echo "varTest2: $varTest2"
echo "varTest3: $varTest3"
echo "-----------------------------------------------"

# Functions with argument and return values
getSum() {

   local res=$(($1 + $2))   # $n: where n indicates argument number

   echo $res    # which will return value to caller
}

num1=4
num2=5
num3=$(getSum $num1 $num2)
echo "Res: $num3"


