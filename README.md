# FTP Server

## Description

This is a simple FTP server written in c.<br>
This FTP server is based on RFC 959.

## Usage

    ./myftp port path
    ./myftp -h

- `port` is the port number on which the server will listen.
- `path` is the path to the root directory of the server.
- `-h` displays the usage.

## Commands

            USER <SP> <username> <CRLF>   : Specify user for authentication
            PASS <SP> <password> <CRLF>   : Specify password for authentication

            CWD  <SP> <pathname> <CRLF>   : Change working directory
            CDUP <CRLF>                   : Change working directory to parent directory

            QUIT <CRLF>                   : Disconnection

            DELE <SP> <pathname> <CRLF>   : Delete file on the server

            PWD  <CRLF>                   : Print working directory

            PASV <CRLF>                   : Enable "passive" mode for data transfer

            PORT <SP> <host-port> <CRLF>  : Enable "active" mode for data transfer


            HELP [<SP> <string>] <CRLF>   : List available commands

            NOOP <CRLF>                   : Do nothing

            (the following are commands using data transfer )

            RETR <SP> <pathname> <CRLF>   : Download file from server to client
            STOR <SP> <pathname> <CRLF>   : Upload file from client to server
            LIST [<SP> <pathname>] <CRLF> : List files in the current working directory

## Creating a user

    ./create_user.sh

The script will ask for a username and a password and will add it in the login.txt file.<br>
The password will automatically be hashed using the XOR algorithm. (it is not secure at all, it is just an example)

## Authors

- [**Maël RABOT**](https://www.linkedin.com/in/mael-rabot/)
