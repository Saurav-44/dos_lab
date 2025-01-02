echo -n "Enter a character: "
read char

if [ ${#char} -ne 1 ]; then
    echo "You have entered more than one character."
    exit 1
fi

if [[ "$char" =~ [a-z] ]]; then
    echo "You entered a lower case alphabet."

elif [[ "$char" =~ [A-Z] ]]; then
    echo "You entered an upper case alphabet."

elif [[ "$char" =~ [0-9] ]]; then
    echo "You have entered a digit."

else
    echo "You have entered a special symbol."
fi
