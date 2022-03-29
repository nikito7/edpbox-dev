#!/bin/sh

# rtu over tcp
HOST="-m enc -p 9502 10.1.0.37"

# serial
#TTY="/dev/ttyS3"
#stty -F $TTY cs8 9600
#HOST="-b 9600 -p none -m rtu $TTY"

function four()
{
/config/apps/modpoll -a 1 -0 -1 -r $1 -c $2 -t 3:int -e $HOST \
| grep '^\[' | awk -F ": " '{ print $2 "," }'

}

result=${result}$(four 38 3)
result=${result}$(four 22 2)

echo $result | sed -e 's/ //g'

##
#
