if [ $# -eq 0 ]; then
   echo "Usage: ./nvwc2 <dtcal>"
   exit 1
fi

FILE=$1

if [ -f "$FILE" ]; then
   LINE_COUNT=$(wc -l < "$FILE")
   WORD_COUNT=$(wc -w < "$FILE")
   CHAR_COUNT=$(wc -m < "$FILE")

   echo "$FILE $LINE_COUNT $WORD_COUNT $CHAR_COUNT"
else
   echo "File $FILE does not exist."
fi
