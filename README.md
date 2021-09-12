TTT COMMANDS
============

TTT COMMANDS is a development commands set to build information system
that could handle large datasets rapidly and flexibly. This gives you 
a way lit power to build a fast process system without some kind of 
databases.  You would build the data process system using only TTT 
COMMANDS, Unix-style basic commands and text datasets on your own favorite 
operating systems.

TTT COMMANDS is licensed under the **[2-clause BSD license](LICENSE)**.

Download
--------

[https://github.com/daichigoto/tttcmds/archive/master.zip](https://github.com/daichigoto/tttcmds/archive/master.zip)

Build and Use
-------------

### FreeBSD 11+

###### PATH

Add tttcmds/bin to the PATH environment variable.

###### Build

    sudo pkg install kyua

    cd tttcmds
    make clean build

### Windows 10+ (You need [Winget](https://github.com/microsoft/winget-cli/))

###### Winget

- Install "[App Installer](https://www.microsoft.com/ja-jp/p/%E3%82%A2%E3%83%97%E3%83%AA-%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%A9%E3%83%BC/9nblggh4nns1)" via Microsoft Store
- Install "[Winget](https://github.com/microsoft/winget-cli/releases)"

###### PATH 

Add the following paths to the PATH environment variable with the following priorities.

1. ${HOME}/Documents/misc/bin/
2. ${HOME}/Documents/tttcmds/bin/
3. C:\msys64\usr\bin
4. C:\msys64\mingw64\bin

###### HOME
Add the environment variable HOME. The value should be the user's home directory, such as "C:\Users\daichi". If this environment variable is not specified, the MSYS2 home directory will be C:\msys64\home\daichi, etc., which is difficult to use.

###### LC_CTYPE

Add the environment variable LC_CTYPE. The value is "ja_JP.UTF-8". If you don't specify this environment variable, MSYS2's vim, etc. will not be able to use Japanese properly.

###### MSYS2 installing 

    winget install MSYS2
    pacman -Syu --noconfirm

###### git installing

    pacman -S --noconfirm git

###### misc buidling and installing

    cd ${HOME}
    mkdir Documents
    cd Documents
    git clone https://github.com/daichigoto/misc.git
    cd misc
    make

###### tttcmds building and installing

    cd ${HOME}
    mkdir Documents
    cd Documents
    git clone https://github.com/daichigoto/tttcmds.git
    cd tttcmds
    make 

### Mac (you need [Homebrew](http://brew.sh/))

###### PATH

Add tttcmds/bin to the PATH environment variable.

###### Build

    brew install bsdmake
    brew install kyua

    cd tttcmds
    bsdmake clean build

### Ubuntu 16.04

###### PATH

Add tttcmds/bin to the PATH environment variable.

    sudo apt-get install clang
    sudo apt-get install libbsd-dev
    sudo apt-get install freebsd-buildutils
    # There is no kyua package for Ubuntu.
    # There is no ATF package for Ubuntu.

###### Build

    cd tttcmds
    bmake clean build

Package Install
---------------

### FreeBSD 11+

    sudo pkg install tttcmds

*Homepage:* https://github.com/daichigoto/tttcmds/
