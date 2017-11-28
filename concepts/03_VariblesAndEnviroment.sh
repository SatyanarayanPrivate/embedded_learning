#!/bin/bash

# System Variables
<<SYSTEM_VARIABLES
    # Print system varibles
        $ printenv or set or env
SYSTEM_VARIABLES

# User Defined variables
<<USER_DEFINED_VARIABLES
varName=someValue
    # if someValue not defined, default null string assigned.
    # do not put spaces either side of variable
USER_DEFINED_VARIABLES
# Example
varSample=sampleData
echo "$varSample"

varSample=10
echo "$varSample"

varSample="sampleData1"
echo "$varSample"

# Integer variable
declare -i varInt=10        # declare integer variable
echo "Integer Var: $varInt"
varInt=strVar
echo "Integer Var: $varInt" # value is null as integer variable

# Constant Variable
# Cannot unset readonly variable
<<CONST_VAR
readonly varName=value
declare -r varName=value
CONST_VAR
declare -r varConst=Constvalue
#varConst=ValUpdate  # error:: varConst: readonly variable
#unset varConst    # error:: varConst: cannot unset: readonly variable

echo "----------------------------------------"

# ${varName} Syntax: to avoid any kind of ambiguity.

# Default shell variables value
echo ${varDef=Default val1} # Such space only allowed in this expression
echo ${varDef-Default val2} # Use val2, if var is not set/ unset
echo "varDef: $varDef"
unset varDef
echo ${varDef-Default val2} # Use val2, if var is not set/ unset
echo "varDef: $varDef"
echo "----------------------------------------"

# ':=' syntax: ${var:=defaultValue}
# If the variable is an empty, assign a default value
var1=val
echo "var1: ${var1:=val1}"  # if var1 is unset then set to val1
unset var1
echo "var1: ${var1:=val3}" 
echo "----------------------------------------"

# Printf command
# printf does not provide a new line
echo "PRINTF"
<<PRINTF
printf "%w.pL\n" $varName
    w - Minimum field width.
    p - Display number of digits after the decimal point (precision).
    L - a conversion character. It can be:
        s - String
        d - Integer
        e - Exponential
        f - Floating point
PRINTF
# Example
vech="Car"
printf "%s\n" $vech     # Car
printf "%1s\n" $vech    # Car
printf "%1.2s\n" $vech
printf "%10.1s\n" $vech
no=10
printf "%d\n" $no
big=5355765
printf "%e\n" $big
printf "%5.2e\n" $big
sales=54245.22
printf "%f\n" $sales
echo "----------------------------------------"

# Quoting
echo "Quoting"
echo "Path is $PATH" # $PATH will be expanded
echo 'I want to print $PATH' # PATH will not be expanded
echo "I want to print \$PATH" # PATH will not be expanded
echo "----------------------------------------"

echo "Arithmatic Operations"
# $((expression))
# $(( n1+n2 ))

# Example
echo "10 + 3: $(( 10 + 3))" 
echo "----------------------------------------"

echo "Path name expansion"
# A curly braces ({..}) expands to create pattern and syntax
echo I like {tom,jerry} # Expands with space
echo file{1,2,3}.txt
echo file{1..3}.txt

echo "----------------------------------------"





