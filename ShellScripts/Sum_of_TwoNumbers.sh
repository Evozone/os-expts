# Write shell script to display addition of two numbers.

echo -n "Enter first number: "
read a
echo -n "Enter second number: "
read b

# Use regex to check if the input is a number
if [[ $a =~ ^[0-9]+$ ]] && [[ $b =~ ^[0-9]+$ ]]
then
    echo "The sum of $a and $b is $(($a + $b))"
else
    echo "Please enter a number"
fi