https://www.modbusdriver.com/modpoll.html

<hr>

2 bytes: Voltage L1:

./modpoll -m enc -a 1 -0 -1 -r 108 -c 1 -t 3 -p 9502 10.1.0.37

modpoll.exe -m rtu -a 1 -0 -1 -r 108 -c 1 -t 3 -b 9600 -p none COM4

<hr>

4 bytes: Total Energy Import:

./modpoll -m enc -a 1 -0 -1 -r 22 -c 1 -t 3:int -e -p 9502 10.1.0.37

modpoll -m rtu -a 1 -0 -1 -r 22 -c 1 -t 3:int -e -b 9600 -p none COM4

