# Write a shell script to find the OS version and the Kernel version of the system.

echo 
echo "============================================="
echo "The Operating System is : "$(uname -o)
echo "The OS "$(grep '^VERSION=' /etc/os-release)
echo "The Release number is : "$(uname -r)
echo "The Kernel Version number is : "$(uname -v)
echo "============================================="
echo