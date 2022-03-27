#!/bin/sh

# rtu over tcp
HOST="-m enc -p 9502 10.1.0.37"

# serial
#HOST="-m rtu /tty...."

function four()
{
/config/apps/modpoll -a 1 -0 -1 -r $1 -c 1 -t 3:int -e $HOST \
grep '^\[' | awk -F : '{ print $2 "," }'

}

four 22


##
#
