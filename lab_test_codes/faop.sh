echo -n "Enter 1st number: "
read n1
echo -n "Enter 2nd number: "
read n2

echo -n  "Choose an operation (+, -, *, /): "
read op

res=$(echo "$n1 $op $n2" | bc -l)

echo "Result: $res"
