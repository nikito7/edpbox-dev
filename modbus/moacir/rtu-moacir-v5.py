#!/usr/bin/python3

###################################################
# This script has beeen tested on Ubuntu 20.04
#
# Created by Moacir Ferreira
# 2021/09/10
# Ver: 0.0001
#
#
#
###################################################

# load necessary modules
import serial
import crcmod
import time
import sys
import paho.mqtt.client as paho

# define file location to save data locally
file_name = "/home/linaro/load_logger.txt"

# configure CRC calculation
crc16 = crcmod.mkCrcFun(0x18005, rev=True, initCrc=0xFFFF, xorOut=0x0000)

# configure serial port
ser = serial.Serial(
            port='/dev/ttyUSB0',          # your serial device ID
            baudrate=9600,                # serial speed
            parity=serial.PARITY_NONE,    # no parity for Kaifa
            stopbits=serial.STOPBITS_ONE, # one stop bit
            bytesize=serial.EIGHTBITS,    # data is eight bits long
            timeout=0)                    # no time out
ser.close()                               # close serial for now, open it when necessary

# function to add CRC to command
def add_crc(data):
    # get CRC and return it in hex with 4 digits
    crc = "0x{:04x}".format((crc16(bytearray.fromhex(data))))
    return(data + crc[4:6] + crc[2:4])

# function to get registers
def get_data(data):
    cmd = bytearray.fromhex(add_crc(data))  # add CRC to the command
    ser.open()                              # open serial
    get = True                              # main loop, get data
    while get:
        ser.flushOutput                     # clear serial output buffer
        ser.flushInput                      # clear serial intput buffer
        ser.write(serial.to_bytes(cmd))     # write request to serial
        time.sleep(0.5)                     # wait a while before reading modbus response...
        resp = ser.read(1).hex()            # read 1 byte from serial
        found = False
        while found == False:               # search for requested response
            c = 0                           # counter to prevent loops
            while resp != data[0:2]:        # check if response comes from the slave you request data
                resp = ser.read(1).hex()    # if not, keep reading serial buffer
                c += 1                      # prevent looping forever
                if c == 32:                 # after reading 32 bytes break the loop if not found
                    break                   # break inner loop
            if c == 32:                     # check if got the loop limit
                break                       # breal outer loop and send command again, restarting the process

            resp = resp + ser.read(1).hex() # found slave number response corret so add the comand and check it
            if resp == data[0:4]:           # break the loop if the response includes the requested sent command
                found = True                # found it, set the variable to break the main loop
            else:

                if resp == data[0:2] + "c5":        # response was an error, expose exception code
                    resp = resp + ser.read(1).hex() # so get error number
                    error = ""
                    x = resp[4:6]
                    if x == "01":
                        error = "Illigal function"
                    if x == "02":
                        error = "Illigal address"
                    if x == "03":
                        error = "Illigal data values"
                    if x == "04":
                        error = "Slave device failure"
                    if x == "81":
                        error = "Access denied"
                    if x == "82":
                        error = "Measurement does not exist"
                    if x == "83":
                        error = "Entry does not exist"
                    if x == "84":
                        error = "Data to retrieve exceeded"
                    sys.exit("Error: " + error)

                resp == ser.read(1).hex()          # if not an error, reset response buffer and start reading from serial again
        if found == True:                          # process info if slave and command response were ok
            resp = resp + ser.read(1).hex()        # so get how many bytes are there to retrieve
            get_more = int(resp[4:6], 16) + 2      # set the number of additional bytes to read and do it, includding CRC
            resp = resp + ser.read(get_more).hex() # get the remaining data
            crc = crc16(bytearray.fromhex(resp))   # check CRC response sanity
            if crc == 0:                           # if CRC is ok, break the main get data loop and return data
                get = False
    ser.close()   # close serial port
    return(resp)  # return colected response

# open mqtt client
client = paho.Client("linaro")
client.username_pw_set(username="mqttuser",password="Thales@123")

if client.connect("172.16.7.150", 1883, 60) != 0:
    sys.exit(-1)

resp = get_data("01440001") # get the data
reg  = []                   # set array to receive extrated data

# load requested data into array 
reg.append(int(resp[6:10],  16)) # reg-0  Year
reg.append(int(resp[10:12], 16)) # reg-1  Month
reg.append(int(resp[12:14], 16)) # reg-2  Day
reg.append(int(resp[16:18], 16)) # reg-3  Hour
reg.append(int(resp[18:20], 16)) # reg-4  Minutes
reg.append(int(resp[32:40], 16)) # reg-5 +A
reg.append(int(resp[56:64], 16)) # reg-6 -A

# publish via mqtt
pub = ("{:0>4d}".format(reg[0])  + "," +
       "{:0>2d}".format(reg[1])  + "," +
       "{:0>2d}".format(reg[2])  + "," +
       "{:0>2d}".format(reg[3])  + "," +
       "{:0>2d}".format(reg[4])  + "," +
       "{:0>12d}".format(reg[5]) + "," +
       "{:0>12d}".format(reg[6])
       )

client.publish("test/status", pub, 0)
client.disconnect()

# write locally to a file
carga = open(file_name, "a+") # Open file
carga.write(pub + "\n")  # write data
carga.close()            # close file

sys.exit(0)
