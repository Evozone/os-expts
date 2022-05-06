# Write shell script to find the number of digits in a number.

echo -n "Enter a number: "
read a

# Use regex to check how many digits the number has
if [[ $a =~ ^[0-9]+$ ]]
then
    echo "The number $a has $((${#a})) digits"
else
    echo "Please enter a number"
fi
