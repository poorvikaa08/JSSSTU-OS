#! /bin/bash

echo "Enter the number of elements in the array: "
read n
echo "Enter the elements of the array: "

for (( i=0; i<n; i++))
do 
    read array[$i]
done

largest=${array[0]}

for (( i=1; i<n; i++))
do 
    if [ ${array[$i]} -gt $largest ]; then
        largest=${array[$i]}
    fi
done

echo "Largest number in the array is: $largest"