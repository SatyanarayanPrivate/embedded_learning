#!/bin/bash

# Looping 

echo "while loop"
counter=10
while [ $counter -ge 0 ]; do    # Continue loop till condition gets false
    echo "counter: $counter"
    counter=$(($counter - 1)) 
done

echo "while loop 1"
counter=5
while [ $counter -ge 0 ]; do    # Continue loop till condition gets false
    echo "counter: $counter"
    counter=$(($counter - 1)) 
done

echo ""
echo "until loop"
counter=1
until [ $counter -ge 10 ]; do   # Continue loop till condition gets true
    echo "counter: $counter"
    counter=$(($counter + 1)) 
done
    

# Break and continue
printf "\nBreak and continue\n"
counter=1
while (( $counter <= 20 )); do
    if (( (($counter % 2)) == 0)); then # Skip even number
        counter=$(($counter + 1))
        continue
    else
        echo "Counter: $counter"
    fi
    if (($counter >= 10)); then 
        break
    fi
    counter=$(($counter + 1))
done

# Read from File 
printf "\nRead from File\n"
while read num1 num2 num3 ; do
    echo "num1: $num1 num2: $num2 num3: $num3"
done < 05_test


# for loop
printf "\nFor looop 1\n"
for (( i=1; i <= 10; i=i+1)); do
    echo "Counter: $i"
done

printf "\nFor looop 2\n"
for i in {1..5}; do
    echo "Counter: $i"
done

printf "\nFor looop 3\n"
for i in {a..d}; do
    echo "Counter: $i"
done

