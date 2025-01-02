echo -n "Enter the cost price of the item: "
read cost_price
echo -n "Enter the selling price of the item: "
read selling_price

if (( selling_price > cost_price )); then
    profit=$((selling_price - cost_price))
    echo "The seller made a profit of: $profit"
elif (( selling_price < cost_price )); then
    loss=$((cost_price - selling_price))
    echo "The seller incurred a loss of: $loss"
else
    echo "No profit, no loss."
fi
