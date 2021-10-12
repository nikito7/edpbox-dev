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

def help():
    print("\nload_chart.py usage:\n")
    print(  "./load_chart.py <start register> <number of readings> <file to save data> <increment step>\n")
    print(  "  Increment step can be any positive or negative number, so incrment or decrement.\n" +
            "  If increment step is not supplied, the default option is to increment readings by 1\n")
    print(  "  I.e.: ./load_chart 1000 96 chart_data.txt 1\n")
    print(  "Note: To get information about available and used profile number of registers do:\n")
    print(  "./load_chart.py info\n")
    sys.exit()

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
                #print("Loop")               # inform there was a loop
                break                       # breal outer loop and send command again, restarting the process

            resp = resp + ser.read(1).hex()     # found slave number response corret so add the comand and check it
            if resp == data[0:4]:               # break the loop if the response includes the requested sent command
                found = True                    # found it, set the variable to break the main loop
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

# function to increment/decrement read register
def inc(data):
    pre  = data[0:6]
    post = data[14:16]
    inc_byte = int(data[6:14], 16) + inc_dec
    return(pre + "{:08x}".format(inc_byte) + post)

######################################
# start processing script command line
######################################

# check parameters on command line
if len(sys.argv) == 1: # check if no parameter were passed
    help()             # if not, print help message and exit
    sys.exit(1)

if len(sys.argv) == 2:        # check if command has been invoked asking info
    if sys.argv[1] == "info": # if so, get info, print and exit
        resp = get_data("010400820002") # read load profile, entries in use
        print("\n    Your meter has " + str(int(resp[14:22],16)) + " profile registers.\n" + 
              "    Out of it, " + str(int(resp[6:14],16))  + " are used.\n")
        sys.exit(0)

if len(sys.argv) < 4 or len(sys.argv) > 5: # check if command has been invoked with right number of parameters
    help()                                 # if not, print help message and exit
    sys.exit(1)

# if got here, everything should be ok, so load necessary variables
start   = sys.argv[1]
get_num = int(sys.argv[2])
save_to = sys.argv[3]
inc_dec = 1
cmd = "014500" + "{:08x}".format(int(start)) + "01"

if len(sys.argv) > 4:          # check if command line was invoked with increment
    inc_dec = int(sys.argv[4]) # if so, set the step number to increment

# Open file to save data
load = open(sys.argv[3], "w+")
load.write( "Reading " + str(get_num) +
            " registers, starting from " +
            sys.argv[1] + ", increment readdings " +
            str(inc_dec) + " on each cycle.\n\n" +
            "Count    Reg.     Command sent        Date        Time        +A                  -A\n"
            )

print( "\nReading " + str(get_num) +
       " registers, starting from " +
       sys.argv[1] + ", increment readdings " +
       str(inc_dec) + " on each cycle.\n\n" +
       "Count    Reg.     Command sent        Date        Time        +A                  -A"
       )

c = 1                    # setup a loop counter
while c <= get_num:      # loop until finished the requested number of registers

    resp = get_data(cmd)          # get the data from the command register
    register = int(cmd[6:14], 16) # save register number being read
    reg  = []                     # set array to receive extrated data

    # load requested data into array 
    reg.append(int(resp[6:10],  16)) # reg-0  Year
    reg.append(int(resp[10:12], 16)) # reg-1  Month
    reg.append(int(resp[12:14], 16)) # reg-2  Day
    reg.append(int(resp[16:18], 16)) # reg-3  Hour
    reg.append(int(resp[18:20], 16)) # reg-4  Minutes
    reg.append(int(resp[20:22], 16)) # reg-5  Seconds
    reg.append(int(resp[32:40], 16)) # +A
    reg.append(int(resp[56:64], 16)) # -A

    # print data on screen
    print(  "{:0>5d}".format(c) + "    " +
            "{:0>5d}".format(register) + "    " + 
            cmd + "    " +
            "{:0>4d}".format(reg[0]) +
            "{:0>2d}".format(reg[1]) +
            "{:0>2d}".format(reg[2]) + "    " +
            "{:0>2d}".format(reg[3]) + ":" +
            "{:0>2d}".format(reg[4]) + ":" +
            "{:0>2d}".format(reg[5])  + "    " +
            "{:0>12d}".format(reg[6]) + ".000    " +
            "{:0>12d}".format(reg[7]) + ".000")

    # save data on the file
    load.write( "{:0>5d}".format(c) + "    " + 
                "{:0>5d}".format(register) + "    " + 
                cmd + "    " +
                "{:0>4d}".format(reg[0]) +
                "{:0>2d}".format(reg[1]) +
                "{:0>2d}".format(reg[2]) + "    " +
                "{:0>2d}".format(reg[3]) + ":" +
                "{:0>2d}".format(reg[4]) + ":" +
                "{:0>2d}".format(reg[5])  + "    " +
                "{:0>12d}".format(reg[6]) + ".000    " +
                "{:0>12d}".format(reg[7]) + ".000\n")

    c += 1
    cmd = inc(cmd)

load.close() # close file

sys.exit(0) # exit sucess
