#!/bin/bash


# Primary expantion

name="Jhon"
echo "${name}'s help"

var1="The dog climb tree"
echo "${var1//dog/cat}"  # string dog replaced with cat

# If var "name" is not defined then val "Derek" assigned. If defined var "name" then value of var will be considered. 
echo "I am ${name:=Derek}"  # Jhon will print, as name already defined

echo "I am ${name1:=Derek}" # Derek will print as name1 is not defined
echo "I am $name1"


# Case statement

read -p "How are you: " age

case $age in
[0-4])      # Check for 0 to 4
    echo "To young for school"
    ;;

5)
    echo "Go to KG"
    ;;
        
[6-9]|1[0-8])               # Check for 6 to 9 or 10 to 18
    #local grade=$((age - 5)) # Local can only be used in function
    grade=$((age - 5))
    echo "Your grade is $grade"
    ;;

*)  # Default case
    echo "Default case"
    ;;
esac    # End of case

# Ternary operator
varVote=0
((age >= 18?(varVote=1):(varVote=0)))
echo "can Vote: $varVote"


# Primary expansion on string

varRandStr="A random string"

echo "String Len: ${#varRandStr}"
echo "from index 3: ${varRandStr:3}"
echo "From 4 to 6: ${varRandStr:4:6}"
echo "From char 't': ${varRandStr#*t}"
