echo -n "Enter content for file1: "
read content1

echo -n "Enter content for file2: "
read content2

echo "$content1" > file1.txt
echo "$content2" > file2.txt

file1="file1.txt"
file2="file2.txt"

if [ ! -f "$file1" ]; then
    echo "Error: File '$file1' does not exist."
    exit 1
fi

if [ ! -f "$file2" ]; then
    echo "Error: File '$file2' does not exist."
    exit 1
fi

if cmp -s "$file1" "$file2"; then
    echo "Files '$file1' and '$file2' have the same content."

    rm "$file2"
    echo "So '$file2' is deleted."
else
    echo "Files '$file1' and '$file2' have different content."
fi
