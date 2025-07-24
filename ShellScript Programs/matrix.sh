#! /bash/bin

echo -n "Enter the order of the matrix (rows and columns): "
read row col

declare -A X
declare -A Y
declare -A Result

echo "Enter elements of first matrix: "
for (( i=0; i<row; i++ ))
do 
    for (( j=0; j<col; j++ ))
    do
        read X[$i,$j]
    done
done

echo "Enter elements of second matrix: "
for (( i=0; i<row; i++ ))
do 
    for (( j=0; j<col; j++ ))
    do
        read Y[$i,$j]
    done
done

for (( i=0; i<row; i++ ))
do 
    for (( j=0; j<col; j++ ))
    do
        Result[$i,$j]=$(( X[$i,$j] + Y[$i,$j] ))
    done
done

echo "Resultant matrix after addition: "
for (( i=0; i<row; i++ ))
do 
    for (( j=0; j<col; j++ ))
    do
        echo -n "${Result[$i,$j]} "
    done
    echo
done