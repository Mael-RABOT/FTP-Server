#!/bin/bash

read -p "Enter username: " username
read -sp "Enter password: " password
echo

key=42
encrypted_password=""
for (( i=0; i<${#password}; i++ )); do
    encrypted_password+=$(printf '%d' $(( $(printf '%d' "'${password:$i:1}") ^ $key )))
done

echo "$username:$encrypted_password" >> login.txt
