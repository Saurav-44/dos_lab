echo -n "Enter a day (e.g., Monday, Tuesday): "
read day

day=$(echo "$day" | tr '[:upper:]' '[:lower:]')

case $day in
    monday)
        echo "No class on Monday";;

    tuesday)
        echo "DOS class time: 2:00 PM - 3:00 PM, Room: 020";;

    wednesday)
        echo "DOS class time: 2:00 PM - 3:00 PM, Room: C-006";;

    thursday)
        echo "DOS class time: 10:00 AM - 11:00 AM, Room: 020";;

    friday)
        echo "DOS class time: 12:00 PM - 1:00 PM, Room: 020";;

    saturday)
        echo "No class on Saturday.";;

    sunday)
        echo "Holiday";;
    *)
        echo "Invalid day entered.";;
esac
