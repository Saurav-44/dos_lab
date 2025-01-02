echo -n "Enter internal mark: "
read internal_mark

echo -n "Enter attendance percentage: "
read attendance_percentage


if (( internal_mark >= 20 && attendance_percentage >= 75 )); then
    echo "Allowed for Semester"
else
    echo "Not Allowed for Semester"
fi
