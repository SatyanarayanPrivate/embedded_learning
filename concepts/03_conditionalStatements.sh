#!/bin/bash

# Conditional

read -p "How ols are you: " age # Store user input in var "age"

if [ $age -ge 18 ]  # Spaces are mandatory  
then
    echo "You can Vote"
elif [ $age -eq 17 ]
then 
    echo "You can Vote Next year"
else
    echo "You Can't Vote"
fi


# Numeric and String comparison

read -p "Enter Number1 Number2: " inNum iNum2

if ((inNum >= 10)); then
    echo "$inNum greater than equal to 10"
fi

if ((inNum == 10)); then
    echo "$inNum equal to 10"
fi

if (( ((inNum % 2)) == 0)); then 
    echo "$inNum is even number"
else
    echo "$inNum is odd number"
fi

if (( ((inNum > 0)) && ((inNum < 10)) )); then 
    echo "$inNum is between 0 amd 10"
fi


# String Comparision

str1=""
str2="sad"
str3="happy"

if [ "$str1" ]; then
    echo "$str1 is not null"
fi

if [ -z "$str1" ]; then
    echo "$str1 is null"
fi

if [ "$str2" == "$str3" ]; then
    echo "$str2 equals to $str3"
elif [ "$str2" != "$str3" ]; then
    echo "$str2 not equals to $str3"
fi

if [ "$str2" > "$str3" ]; then
    echo "$str2 greater than $str3"
elif [ "$str2" < "$str3" ]; then
    echo "$str2 less than $str3"
fi



