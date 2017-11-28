#!/bin/bash

# Functions 
<<FUNCTION
# All shell functions are treated as a command.
# Must define a function at the start of a script.
# Must load a function file at the start of a script using source (or .) command
    $ source sampleScript.sh
# Returning from a function: Return back the value (true or false) to the script
    return N
    # If N is not specified, the return status is that of the last command.
    # The return command terminates the function.
    # The return command is not necessary when the return value is that of the last command executed
# Returning a string or word from a function
    # Cannot return a word or anything else from a function.
    # Can use echo or printf command to send back output easily to the script.
# Putting function in background
    funName () {}
    funName &   # Will put function in background
FUNCTION

# Simple function calling
getDate(){
    date
    return 
}

getDate
echo "-----------------------------------------------"

# Globle and local variable"
# local command can only be used within a function 
# It makes the variable name have a visible scope restricted to that function and its children only

varTest1="Globle Var1"
varTest2="Globle Var2"
demoLocal2() {
    echo "demoLocal2"
    echo "varTest1: $varTest1"  # demoLocal1 variable value changed
    varTest1="Updated in Local2"
    return
}

demoLocal1(){
    local varTest1="Local Var1" 
    varTest3="Test3"  # it will consider as global variable
    echo "varTest1: $varTest1"
    echo "varTest2: $varTest2"
    echo "varTest3: $varTest3"
    demoLocal2 
    echo "varTest1: $varTest1"
    varTest2="Var2 Value Changed"
    return
}

demoLocal1

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


echo "One line function"
# One line functions inside { ... } must end with a semicolon. Otherwise you get an error on screen
# functionName() { command1; command2; commandN;}
fun1(){ echo "command 1"; echo "command 2";}
fun1
echo "-----------------------------------------------"

echo "Removing function"
fun2(){ echo "command 1"; echo "command 2";}
fun2
unset fun2
#fun2   # error:: fun2: command not found
echo "-----------------------------------------------"

