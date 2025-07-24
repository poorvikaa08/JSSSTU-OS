#! /bin/bash

echo "Enter three numbers: "
read a b c

if [ $a -ge $b ] && [ $a -ge $c ]; then
    largest=$a
elif [ $b -ge $a ] && [ $b -ge $c ]; then
    largest=$b
else 
    largest=$c
fi

echo "Largest number is: $largest"

