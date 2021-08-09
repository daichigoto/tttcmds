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

Installation
------------

### Install some packages required for build

* FreeBSD 11+

        sudo pkg install kyua

* Darwin 16.0.0+ (you need a [brew](http://brew.sh/))

        brew install bsdmake
        brew install kyua

* Ubuntu 16.04

        sudo apt-get install clang
        sudo apt-get install libbsd-dev
        sudo apt-get install freebsd-buildutils
        # There is no kyua package for Ubuntu.
        # There is no ATF package for Ubuntu.

### Build and install

* FreeBSD 11+

        make clean build
        sudo make install

* Darwin 16.0.0+

        bsdmake clean build
        sudo bsdmake install

* Ubuntu 16.04

        bmake clean build
        sudo bmake install

### Install using packages

* FreeBSD 11+

	sudo pkg install tttcmds

*Homepage:* https://github.com/daichigoto/tttcmds/
