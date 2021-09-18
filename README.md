TTT COMMANDS
============

TTT COMMANDS is a development commands set to build information system
that could handle large datasets rapidly and flexibly. This gives you 
a way lit power to build a fast process system without some kind of 
databases.  You would build the data process system using only TTT 
COMMANDS, Unix-style basic commands and text datasets on your own favorite 
operating systems.

TTT COMMANDS is licensed under the **[2-clause BSD license](LICENSE)**.

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

1. ${HOME}\Documents\misc\bin
2. ${HOME}\Documents\tttcmds\bin
3. C:\msys64\usr\bin
4. C:\msys64\mingw64\bin

The starting point for the build is ${HOME}\Documents\misc\bin\make.ps1. Therefore, it is necessary to add ${HOME}\Documents\misc\bin\ to the environment variable PATH with the highest priority so that it will be the first target of the search.

###### HOME

Add the environment variable HOME. The value should be the user's Windows home directory, such as "C:\Users\daichi". If this environment variable is not specified, the MSYS2 home directory will be like C:\msys64\home\daichi where is not home directory of Windows.

Windows home directory and MSYS2 home directory are different. By setting the value of the environment variable HOME as described above, you can change the home directory of MSYS2 to the home directory of Windows. If you want to use Windows and MSYS2 in a more integrated way, this setting can help. If you want to keep your home directory different, there is no need to set the environment variable HOME.

###### LC_CTYPE

Add the environment variable LC_CTYPE. The value is your locale like "ja_JP.UTF-8". If you don't specify this environment variable, MSYS2's vim, etc. will not be able to use non-ascii language properly.

When you have finished adding environment variables, quit all Windows Terminal and start a new Windows Terminal. If you do not quit the Windows Terminal, the PATH environment variable you set will not be reflected.

###### MSYS2 installing 

    winget install MSYS2
    pacman -Syu --noconfirm

###### git installing

    pacman -S --noconfirm git

###### misc buidling and installing

    cd ${HOME}\Documents
    git clone https://github.com/daichigoto/misc.git
    cd misc
    make

###### tttcmds building and installing

    cd ${HOME}\Documents
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

###### Build

    sudo apt-get install clang
    sudo apt-get install libbsd-dev
    sudo apt-get install freebsd-buildutils
    # There is no kyua package for Ubuntu.
    # There is no ATF package for Ubuntu.
    
    cd tttcmds
    bmake clean build

Package Install
---------------

### FreeBSD 11+

    sudo pkg install tttcmds

Download
--------

[https://github.com/daichigoto/tttcmds/archive/master.zip](https://github.com/daichigoto/tttcmds/archive/master.zip)

*Homepage:* https://github.com/daichigoto/tttcmds/
