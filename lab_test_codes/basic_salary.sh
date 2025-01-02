echo -n "Enter Ramesh's basic salary: "
read basic_salary

da=$(echo "0.4 * $basic_salary" | bc)

hra=$(echo "0.2 * $basic_salary" | bc)

gross_salary=$(echo "$basic_salary + $da + $hra" | bc)

echo "Ramesh's gross salary is: $gross_salary"
