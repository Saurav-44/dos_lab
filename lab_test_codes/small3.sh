echo -n "Enter 1st number: "
read n1
echo -n "Enter 2nd number: "
read n2
echo -n "Enter 3rd number: "
read n3

if (( n1 <= n2 && n1 <= n3 )); then
    smallest=$n1
elif (( n2 <= n1 && n2 <= n3 )); then
    smallest=$n2
else
    smallest=$n3
fi

echo "The smallest number is: $smallest"
