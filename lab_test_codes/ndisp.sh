if [ $# -ne 3 ]; then
   echo "Usage: ./ndisp <n> <m> <file.txt>"
   exit 1
fi

N=$1
M=$2
FILE=$3

if [ ! -f "$FILE" ]; then
   echo "File $FILE does not exist."
   exit 1
fi

echo "First $N lines of $FILE:"
head -n $N "$FILE"

echo

echo "Last $M lines of $FILE:"
tail -n $M "$FILE"
