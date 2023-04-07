#!/bin/bash

# Check if Anonsurf is installed
if ! sudo anonsurf status | grep -q "tor.service"; then
  echo "AnonSurf is not Installed.... Installing...."
  sudo git clone https://github.com/Und3rf10w/kali-anonsurf.git
else
  echo "Anonsurf is already installed."

fi


echo " "

# Check if curl is installed
if hash curl 2>/dev/null; then
  echo "curl is already installed."
else
  echo "curl is not installed. Installing curl now..."
  sudo apt-get install curl
fi

echo " "

# Check if grep is installed
if hash grep 2>/dev/null; then
  echo "grep is already installed."
else
  echo "grep is not installed. Installing grep now..."
  sudo apt-get install grep
fi

echo " "

# Check if awk is installed
if hash awk 2>/dev/null; then
  echo "awk is already installed."
else
  echo "awk is not installed. Installing awk now..."
  sudo apt-get install awk
fi

echo " "


# Check if sshpass is installed
if hash sshpass 2>/dev/null; then
  echo "sshpass is already installed."
else
  echo "sshpass is not installed. Installing sshpass now..."
  sudo apt-get install sshpass
fi

echo " "


# Check if ssh is installed
if hash ssh 2>/dev/null; then
  echo "ssh is already installed."
else
  echo "ssh is not installed. Installing ssh now..."
  sudo apt-get install ssh
fi

echo " "


# Check if whois is installed
if hash whois 2>/dev/null; then
  echo "whois is already installed."
else
  echo "whois is not installed. Installing whois now..."
  sudo apt-get install whois
fi

echo " "


# Check if nmap is installed
if hash nmap 2>/dev/null; then
  echo "nmap is already installed."
else
  echo "nmap is not installed. Installing nmap now..."
  sudo apt-get install nmap
fi

echo " "


# Check if scp is installed
if hash scp 2>/dev/null; then
  echo "scp is already installed."
else
  echo "scp is not installed. Installing scp now..."
  sudo apt-get install scp
fi

echo " "

# Check if the connection is anonymous via AnonSurf
if ! sudo anonsurf status | grep -q "Active: active"; then
  echo "Error: Your connection is not anonymous via AnonSurf."
  exit 1
fi

# Display the spoofed country name
echo "Your connection is anonymous via AnonSurf. Your location is being spoofed as: $(curl --silent -x socks5h://localhost:9050 https://ipapi.co/country_name/)"

# Allow the user to specify the Domain/IP Address
echo -n "Enter the IP Address: "
read target

# Allow the user to specify the username
echo -n "Enter the username: "
read username

# Ask the user for their password
read -s -p "Enter the password: " password
echo

# Connect to the remote server via port 5511
sshpass -p $password ssh -p 5511 $username@$target << EOF

# Get the details of the remote server
echo "--- Remote Server Details ---"
echo "Country: $(curl -s https://ipapi.co/country_name/)"
echo "IP: $(curl -s https://ipapi.co/ip/)"
echo "Uptime: $(uptime | awk '{print $3,$4}')"

# Check the Whois of the given address
echo "--- Whois Information ---"
whois $target > whois_$target.txt

# Scan for open ports on the given address
echo "--- Port Scan ---"
nmap -p- $target > nmap_$target.txt

EOF

# Copy the output files to the local computer
scp -P 5511 $username@$target:~/whois_$target.txt .
scp -P 5511 $username@$target:~/nmap_$target.txt .

# Create a log and audit of the data collection
echo "Data collected on $(date +%F_%T) for address $target" >> data_collection.log
echo "Whois data saved in file whois_$target.txt" >> data_collection.log
echo "Nmap data saved in file nmap_$target.txt" >> data_collection.log
