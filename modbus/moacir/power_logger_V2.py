#!/usr/bin/python3

# load necessary Python modules
import serial
import crcmod
import time
import sys
import paho.mqtt.client as paho
import datetime
from os.path import exists
import os
import syslog

### CHANGE TO MATCH YOUR SYSTEM ######################################
MQTT_SERVER   ="127.0.0.1"         # MQTT broker address
MQTT_USER     =""             # MQTT user name to be used
MQTT_PASSWORD =""           # MQTT user password
MQTT_TOPIC_1  ="kaifa/diagram"        # topic to publish load map
MQTT_TOPIC_2  ="kaifa/counters"       # topic to publish common data
SERIAL_PORT   ='/dev/ttyUSB0'         # serial port to be used
BAUD_RATE     ='9600'                 # baudrate to be used
FILE_DIR      ="./data/"  # directory to save data
######################################################################

# configure, open and close serial port
try:
    ser = serial.Serial(
                port=SERIAL_PORT,             # your serial device ID
                baudrate=BAUD_RATE,           # serial speed
                parity=serial.PARITY_NONE,    # no parity (most of meters)
                stopbits=serial.STOPBITS_ONE, # one stop bit
                bytesize=serial.EIGHTBITS,    # data is eight bits long
                timeout=0)                    # no time out
except IOError:                               # error, report it
    syslog.syslog(syslog.LOG_ERR, "Could not open serial port " + SERIAL_PORT)
    sys.exit(-1)
ser.close()                                   # close serial for now

# create a last month file name to save data locally
LAST_MONTH = (FILE_DIR +
            "{:0>2d}".format(datetime.datetime.today().year)      +
            "{:0>2d}".format(datetime.datetime.today().month - 1) +
            ".csv")

# create a current month file name to save data locally
THIS_MONTH  = (FILE_DIR +
            "{:0>2d}".format(datetime.datetime.today().year)  +
            "{:0>2d}".format(datetime.datetime.today().month) +
            ".csv")

# open file and create headers if it is a new csv file
try:
    load_map = open(THIS_MONTH, "a+") # open file
except IOError:                       # error, report it
    syslog.syslog(syslog.LOG_ERR, "Could not open file " + THIS_MONTH)
    sys.exit(-1)
load_map.seek(0, os.SEEK_SET)         # go to the first line of the file
first_line = load_map.readline()      # read the first line (headers)
if first_line == '':                  # if it is a new file, write headers on it
    load_map.write("date,hour,imported,exported\n")
load_map.close()                      # close file

# configure CRC calculation
crc16 = crcmod.mkCrcFun(0x18005, rev=True, initCrc=0xFFFF, xorOut=0x0000)

# function to add CRC to command
def add_crc(data):
    # get CRC and return it in hex with 4 digits
    crc = "0x{:04x}".format((crc16(bytearray.fromhex(data))))
    return(data + crc[4:6] + crc[2:4])

# function to get register data
def get_data(data):
    ser.open()                              # open serial port
    ser.flushOutput                         # clear serial output buffer
    ser.flushInput                          # clear serial intput buffer
    cmd = bytearray.fromhex(add_crc(data))  # add CRC to the command
    got = 1                                 # main loop, get data
    loop = 1                                # counter to prevent main for looping forever
    while got:                              # main loop until get valid response to command
        ser.write(serial.to_bytes(cmd))     # write request to serial
        resp = ser.read(1).hex()            # read 1 byte from the serial
        c = 0                               # counter to prevent sub loop for looping forever
        while resp != data[0:2]:            # check up if response comes from the right slave
            time.sleep(0.1)                 # wait a while before reading a modbus response...
            resp = ser.read(1).hex()        # if not, keep reading serial buffer
            c += 1                          # prevent looping forever
            if c == 10:                     # it is a loop or something is wrong, so break this loop
                break
        resp = resp + ser.read(1).hex()     # possibly found slave number response corret so add the command and check it
        if resp == data[0:4]:               # break the loop if the response includes the requested sent command
            resp = resp + ser.read(1).hex()        # get how many bytes are there to retrieve
            get_more = int(resp[4:6], 16) + 2      # set the number of additional bytes to read and do it, includding CRC
            resp = resp + ser.read(get_more).hex() # get the remaining data
            crc = crc16(bytearray.fromhex(resp))   # check CRC response sanity
            if crc == 0:                           # check if CRC is ok
                got = 0                            # got good data, break the main get data loop and return data
        loop += 1                            # increment main loop counter
        if loop == 10:                       # reach maximum tries, break entire script and log it on syslog
            syslog.syslog(syslog.LOG_ERR, "There was a loop or RS485 read failure")
            sys.exit(-1)        
    ser.close()                              # close serial port
    return(resp)                             # return colected data


# get data
reg  = []                        # set array to receive all requested data
resp = get_data("01440001")      # request last profile
reg.append(int(resp[ 6:10], 16)) # reg-0  last profile year
reg.append(int(resp[10:12], 16)) # reg-1  last profile month
reg.append(int(resp[12:14], 16)) # reg-2  last profile day
reg.append(int(resp[16:18], 16)) # reg-3  last profile hour
reg.append(int(resp[18:20], 16)) # reg-4  last profile minutes
reg.append(int(resp[32:40], 16)) # reg-5  last profile +A
reg.append(int(resp[56:64], 16)) # reg-6  last profile -A

resp = get_data("010400160002")  # request total imported and exported
reg.append(int(resp[6:14], 16))  # reg-7  imported total
reg.append(int(resp[14:22], 16)) # reg-8  exported total

resp = get_data("010400260003")  # request imported contract 1, 2 and 3
reg.append(int(resp[6:14], 16))  # reg-9  imported contract 1 (vazio)
reg.append(int(resp[14:22], 16)) # reg-10 imported contract 2 (ponta)
reg.append(int(resp[22:30], 16)) # reg-11 imported contract 3 (cheia)

resp = get_data("0104002D0003")  # request exported contract 1, 2 and 3
reg.append(int(resp[6:14], 16))  # reg-12 exported contract 1 (vazio)
reg.append(int(resp[14:22], 16)) # reg-13 exported contract 2 (ponta)
reg.append(int(resp[22:30], 16)) # reg-14 exported contract 3 (cheia)

resp = get_data("0104006C0001")  # request voltage
reg.append(int(resp[6:10], 16))  # reg-15 voltage

resp = get_data("010400740001")  # request Instantaneous active power on L1
reg.append(int(resp[6:10], 16))  # reg-16 production power

# assemble data to be written to the file and MQTT topic 1
msg_1 = ("{:0>4d}".format( reg[0])  +
         "{:0>2d}".format( reg[1])  +
         "{:0>2d}".format( reg[2])  + "," +
         "{:0>2d}".format( reg[3])  +
         "{:0>2d}".format( reg[4])  + "," +
         "{:0>12d}".format(reg[5])  + "," +
         "{:0>12d}".format(reg[6])
        )

# assemble data to be written to MQTT topic 2
msg_2 = ("{:0>12d}".format(reg[7])  + "," +
         "{:0>12d}".format(reg[8])  + "," +
         "{:0>12d}".format(reg[9])  + "," +
         "{:0>12d}".format(reg[10]) + "," +
         "{:0>12d}".format(reg[11]) + "," +
         "{:0>12d}".format(reg[12]) + "," +
         "{:0>12d}".format(reg[13]) + "," +
         "{:0>12d}".format(reg[14]) + "," +
         "{:0>4d}".format(reg[15])  + "," +
         "{:0>12d}".format(reg[15])
         )
print(msg_2)

# process load map
# check time to write the last load map record on last month file
FILE = ""
if (datetime.datetime.today().day    == 1 and
    datetime.datetime.today().hour   == 0 and
    datetime.datetime.today().minute < 15):
    FILE = LAST_MONTH
else:
    FILE = THIS_MONTH

try:
    load_map = open(FILE, "a+")         # open file
except IOError:                         # error, report it
    syslog.syslog(syslog.LOG_ERR, "Could not open file " + FILE)
    sys.exit(-1)
load_map.seek(0, os.SEEK_SET)           # go to the first line of the file
last_line = load_map.readlines() [-1:]  # read the last line of the file

if last_line[0] == (msg_1 + "\n"):      # check if csv has the latest load data
    load_map.close()                    # if so, close file
else:                                   # if not,
    load_map.write(msg_1 + "\n")        # write new data to the file
    load_map.close()                    # close file

    # publish data via MQTT
    client = paho.Client("PowerReader") # open MQTT handle
    if client.connect(MQTT_SERVER, 1883, 60) != 0:
        syslog.syslog(syslog.LOG_ERR, "Could not connect to MQTT broker")
        sys.exit(-1)
    else:
        client.username_pw_set(username=MQTT_USER,password=MQTT_PASSWORD)
        client.publish(MQTT_TOPIC_1, msg_1, 0) # publish data
        client.disconnect()                    # close MQTT connection

# publish remaining data via MQTT
client = paho.Client("PowerReader")     # open MQTT connection
if client.connect(MQTT_SERVER, 1883, 60) != 0:
    syslog.syslog(syslog.LOG_ERR, "Could not connect to MQTT broker")
    sys.exit(-1)
else:
    client.username_pw_set(username=MQTT_USER,password=MQTT_PASSWORD)
    client.publish(MQTT_TOPIC_2, msg_2, 0) # publish data
    client.disconnect()                    # close MQTT connection

sys.exit(0)
