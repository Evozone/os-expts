# Write shell script to display substring from Main string (e.g consider string is “Welcome to the world of technology” from this display substring from position 6 to 12) 

echo -n "Enter a string: "
read a
echo -n "Enter a position: "
read pos1
echo -n "Enter another position: "
read pos2

if [[ $pos1 =~ ^[0-9]+$ ]] && [[ $pos2 =~ ^[0-9]+$ ]]
then
    echo "The substring is ${a:$pos1:$pos2}"
else
    echo "Please enter a number"
fi