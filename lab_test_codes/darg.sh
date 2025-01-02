echo "Total number of arguments: $#"

if [ $# -ge 2 ]; then
   echo "First argument: $1"
   echo "Second argument: $2"
else
   echo "Not enough argument provided."
fi

echo "All arguments: $@"


