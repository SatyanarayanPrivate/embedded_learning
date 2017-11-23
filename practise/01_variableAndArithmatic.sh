#!/bin/bash

echo ""
echo "----------------- Variable -----------------"
    # Variable
    # Should start with leeter or '_' and may contain numbers
    # Should not have white spaces on either side of varible name 

numVar_1=5 # numeric variable
echo "Numeric Var: $numVar_1"
echo "Numeric Var: $((numVar_1))"  # Print value of within expression '((--))'
echo "Numeric Var: $(( numVar_1))" # Spaces within expressions are allowed

myVar_1="TestVariable1" # string variable
echo "String Var: $myVar_1"
echo "String Var: $((myVar_1))" # prints zero:  ???

charVar_1='s' # Char variable
echo "Char Var: $charVar_1"
echo "Char Var: $((charVar_1))" # prints zero:  ???

    # Constant variable
declare -r constVar_1=7
echo "constant Var: $constVar_1"
echo "constant Var: $((constVar_1))"

echo ""
echo "----------------- Arithmatic -----------------"
num1=2
num2=4
res1=$((num1 + num2))
echo "num1 + num2 : $res1"
let res1+=3
echo "res1 += 3: $res1"
echo "res1 : $res1"
echo "res1++: $((res1++))" # First prints value then increament
echo "++res1: $((++res1))" # First increament value then print value

    # Ariothmatic of Floating varible
        # bash doesn't support floats
        # you have the luxury to use different shells other than bash
floatingVar_1=1.3
floatingVar_2=1.6
res2=$(python -c "print $floatingVar_1+$floatingVar_2")
echo "Floating arithmatic: $res2"
