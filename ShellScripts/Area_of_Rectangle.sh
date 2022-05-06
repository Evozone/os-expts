# Write shell script to display area of rectangle.

echo -n "Enter length of rectangle: "
read length
echo -n "Enter width of rectangle: "
read width

# Use regex to check if the input is a floating point number
if [[ $length =~ ^[0-9]+$ ]] && [[ $width =~ ^[0-9]+$ ]]
then
    echo "The area of the rectangle is $(($length * $width))"
else
    echo "Please enter a number"
fi