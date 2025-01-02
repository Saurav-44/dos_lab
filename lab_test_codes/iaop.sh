echo "Enter 1st number: "
read n1
echo "Enter 2nd number: "
read n2

echo "Choose an operation to perform:"
echo "1. Addition"
echo "2. Substraction"
echo "3. Multiplication"
echo "4. Division"
read choice

case $choice in
     1)  res=$((n1 + n2))
         echo "Addition: $res"
         ;;
     2)  res=$((n1 - n2))
         echo "Substraction: $res"
         ;;
     3)  res=$((n1 * n2))
         echo "Multiplication: $res"
         ;;
     4)  if [ $n2 -ne 0 ]; then
            res=$((n1 / n2))
            echo "Division: $res" 
         else
            echo "Division by 0 is not allowed."
         fi
         ;;
     *)  echo "Invalid choice"
         ;;
esac 
