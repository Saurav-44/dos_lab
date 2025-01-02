FILE="dtcal"

if [ -f "$FILE" ]; then
   LINE_COUNT=$(wc -l < "$FILE")
   WORD_COUNT=$(wc -w < "$FILE")
   CHAR_COUNT=$(wc -m < "$FILE")

   echo "Filename: $FILE"
   echo "Line count: $LINE_COUNT"
   echo "Word count: $WORD_COUNT"
   echo "Char count: $CHAR_COUNT"
else
   echo "File $FILE does not exist."
fi

