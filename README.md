# FTP Server

## Description

This is a simple FTP server written in c.<br>
It is based on RFC 959.

## Usage

    ./myftp port path
    ./myftp -h

- `port` is the port number on which the server will listen.
- `path` is the path to the root directory of the server.
- `-h` displays the usage.

## Commands

- `USER <username>`: authenticate the user.
- `PASS <password>`: authenticate the user.
- `CWD <path>`: change the working directory.
- `CDUP`: change the working directory to the parent directory.
- `PWD`: print the working directory.
- `QUIT`: close the connection.
- `DELE <path>`: delete the file at the specified path.
- `PASV`: enter passive mode.
- `PORT <h1,h2,h3,h4,p1,p2>`: enter active mode.
- `HELP`: display the list of available commands.
- `NOOP`: do nothing.
- `RETR <path>`: download the file at the specified path.
- `STOR <path>`: upload the file at the specified path.
- `LIST`: list the files in the current directory.

## Authors

- [**Maël RABOT**](https://www.linkedin.com/in/mael-rabot/)
