# Write shell script to concatenate the inputted strings during runtime. 

echo -n "Enter a string: "
read a
echo -n "Enter another string: "
read b

c=$a$b

echo "The concatenated string is $c"