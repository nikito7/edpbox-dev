#!/usr/bin/python3

# Call this script as:
# python3 estudo.py 014500000000FF01
#
# then increment register:
# python3 estudo.py 0145000000010001

# load necessary modules
import serial
import crcmod
import time
import sys

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

# function to get data
def get_data(data):
    cmd = bytearray.fromhex(add_crc(data)) # add CRC to the command
    ser.open()                             # open serial
    get = True                             # main loop, get data
    while get:
        ser.flushOutput                    # clear serial output buffer
        ser.flushInput                     # clear serial intput buffer
        ser.write(serial.to_bytes(cmd))    # write request to serial
        time.sleep(0.5)                    # wait a while before reading modbus response...
        resp = ser.read(1).hex()           # read 1 byte from serial
        found = False
        while found == False:              # search for requested response
            c = 0                          # counter to prevent loops
            while resp != data[0:2]:       # check if response comes from the slave you request data
                resp = ser.read(1).hex()   # if not, keep reading serial buffer
                c += 1                     # prevent looping forever
                if c == 32:                # after reading 32 bytes break the loop if not found
                    break
            if c == 32:                     # check if got the loop limit
                print("Loop")               # inform there was a loop
                break                       # there was a loop; break it and stop from reading more from serial

            resp = resp + ser.read(1).hex() # found slave number response corret, add comand and check it
            if resp == data[0:4]:           # if the response includes the requested command, get byte count of it
                resp = resp + ser.read(1).hex()
                found = True                # found it, set the variable to break the main loop
            else:
                resp == ser.read(1).hex()   # if not, reset response buffer and start reading from serial again

        if found == True:                   # process if slave and command response is ok
            resp = resp + ser.read(1).hex() # get how many bytes are there to retrieve
            get_more = int(resp[4:6], 16) + 2      # set the number of additional bytes to read and do it
            resp = resp + ser.read(get_more).hex() # get the remaining data

            crc = crc16(bytearray.fromhex(resp)) # check CRC response sanity
            if crc == 0:                         # if CRC is ok, break the main get data loop
                get = False
    ser.close()                             # close serial port
    return(resp)

resp = get_data(sys.argv[1]) # get the data from the command register

reg = []                     # array to receive extrated data

reg.append(int(resp[6:10],  16)) # reg-0  Year
reg.append(int(resp[10:12], 16)) # reg-1  Month
reg.append(int(resp[12:14], 16)) # reg-2  Day
reg.append(int(resp[16:18], 16)) # reg-3  Hour
reg.append(int(resp[18:20], 16)) # reg-4  Mimutes
reg.append(int(resp[20:22], 16)) # reg-5  Seconds

print(str(reg[0]) + "/" + str(reg[1]) + "/" + str(reg[2]) + "-" + str(reg[4]) + ":" + str(reg[5]))

sys.exit()
