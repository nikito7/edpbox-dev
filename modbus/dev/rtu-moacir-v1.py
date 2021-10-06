#!/usr/bin/python3

# load necessary modules
import serial
import crcmod
import sys
import time

# check if arguments were passed to this scrip
# if not, abort
arg_num = len(sys.argv)
if arg_num == 1:
    print("You must supply a command.")
    sys.exit()

# configure CRC calculation
crc16 = crcmod.mkCrcFun(0x18005, rev=True, initCrc=0xFFFF, xorOut=0x0000)

# configure and open serial port
ser = serial.Serial(
            port='/dev/ttyUSB0',
            baudrate=9600,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=0.8)

# add CRC to command
def add_crc(to_add):
    cmd = bytearray.fromhex(to_add)
    # make sure CRC will always be 6 digits
    crc = "0x{:04x}".format((crc16(cmd)))
    # append CRC to command
    cmd.append(int(crc[4:6], 16))
    cmd.append(int(crc[2:4], 16))
    return(cmd)

# process command line
cmd = add_crc(sys.argv[1])
# clean serial port output buffer
ser.flushOutput
get = True
while get:
    # wait for modbus silence
    wait = ser.readline().hex()
    while wait != "":
        wait = ser.readline().hex()
    # sleep for modbus standard
    time.sleep(0.35)
    ser.flushInput
    # write command
    ser.write(serial.to_bytes(cmd))
    # get response
    resp = ser.readline().hex()
    # CRC response sanity check
    crc = crc16(bytearray.fromhex(resp))
    if crc == 0:
        # response lenght
        if sys.argv[2].upper() == "DL":
            if len(resp) == 26:
                print("CRC ok and lenght ok")
                get = False
# get requested info
reg1 = resp[6:14]
reg2 = resp[14:22]
#######################
print("Command was: " + sys.argv[1])
print("Response was: " + resp)
print("Register 1 is: " + str(int(reg1, 16)))
print("Register 2 is: " + str(int(reg2, 16)))
ser.close()
