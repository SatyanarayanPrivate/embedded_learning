#!/bin/bash

# Arrays

varArr=(11 2.2 0.33 44)

echo "varArr[1]: ${varArr[1]}"  # Get value of index 1

varArr[0]=1.11 # Update value of Array
echo "varArr[0]: ${varArr[0]}" 

varArr[4]=55.21 # updating Array with single element
echo "varArr[4]: ${varArr[4]}" 

varArr+=(6 21.1) # updating Array with multiple element
echo "{varArr[*]}: ${varArr[*]}"    # ???
for i in ${varArr[*]}; do   # With array
    echo "$i"
done
echo "---------------------"

echo "{varArr[@]}: ${varArr[@]}"    # ???
for i in ${varArr[@]}; do
    echo "$i"
done

# Length of Array
echo "Array Len: ${#varArr[@]}"
echo "Index 4 Len: ${varArr[4]} ${#varArr[4]}"

# Delete elememts from Array
echo "{varArr[*]}: ${varArr[*]}"
unset 'varArr[0]'
echo "{varArr[*]}: ${varArr[*]}"


