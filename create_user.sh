#!/bin/bash

read -p "Enter username: " username
read -sp "Enter password: " password
echo

key=42
encrypted_password=""
for (( i=0; i<${#password}; i++ )); do
    encrypted_password+=$(printf '%d' $(( $(printf '%d' "'${password:$i:1}") ^ $key )))
done

while True; do
    read -p "Enter permission level (0 or 1): " permission
    if [[ "$permission" == "0" ]] || [[ "$permission" == "1" ]]; then
        break
    else
        echo "Invalid permission level. Please enter 0 or 1."
    fi
done

echo "$username:$encrypted_password:$permission" >> login.txt
