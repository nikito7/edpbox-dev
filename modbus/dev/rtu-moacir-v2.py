#!/usr/bin/python3

# load necessary modules
import serial
import crcmod
import time
import sys

# configure CRC calculation
crc16 = crcmod.mkCrcFun(0x18005, rev=True, initCrc=0xFFFF, xorOut=0x0000)

# configure serial port
ser = serial.Serial(
            port='/dev/ttyUSB0', # you may need to change this...
            baudrate=9600,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=0.5)
ser.close()

# define functions
##################

# add CRC to command
def add_crc(to_add):
    cmd = bytearray.fromhex(to_add)
    # make sure CRC will always be 6 digits
    crc = "0x{:04x}".format((crc16(cmd)))
    # append CRC to command and return it
    cmd.append(int(crc[4:6], 16))
    cmd.append(int(crc[2:4], 16))
    return(cmd)

def get_data(hex_cmd):
    # process command line
    cmd = add_crc(hex_cmd)
    # open and clean serial output buffer
    ser.open()
    ser.flushOutput
    get = True
    while get:
        # wait for modbus silence
        wait = ser.readline().hex()
        while wait != "":
            wait = ser.readline().hex()
        # sleep for modbus standard
        time.sleep(0.35)
        # write command
        ser.flushInput
        ser.write(serial.to_bytes(cmd))
        # get 3 bytes from response to learn how
        # many bytes more need to be read
        resp = ser.read(3).hex()
        while len(resp) != 6:
            resp = ser.read(3).hex()
        # set the number of additional byte to read and do it
        get_more = int(resp[4:6], 16) + 2
        resp = resp + ser.read(get_more).hex()
        # icheck CRC response sanity
        crc = crc16(bytearray.fromhex(resp))
        # check if it a error message
        # if not an error repeat the process til get
        # a valid response
        if crc == 0:
            get = False
    ser.close()
    return(resp)

# function to increment read register
def inc(data):
    base = data[0:10]
    inc_byte = int(data[10:14], 16)
    inc_byte += 1
    end = data[14:16]
    return(base + "{:04x}".format(inc_byte) + end)

# Open file to save data
carga = open("carga.csv", "w+")

# write colum names
carga.write("Time,AMR,A+,+Ri,-Rc,-A,-Ri,+Rc\n") 

#start = "0145000000000001"
start = sys.argv[1]
c = 1
while c <= int(sys.argv[2]):
    print("Colecting register " + start)
    resp = get_data(start)
    start = inc(start)
    c += 1
    reg = []
    if resp[0:4] == "0145":
        reg.append(int(resp[6:10],  16))
        reg.append(int(resp[10:12], 16))
        reg.append(int(resp[12:14], 16))
        reg.append(int(resp[14:16], 16))
        reg.append(int(resp[16:18], 16))
        reg.append(int(resp[18:20], 16))
        reg.append(int(resp[20:22], 16))
        reg.append(int(resp[22:24], 16))
        reg.append(hex(int(resp[24:28], 16)))
        reg.append(hex(int(resp[28:30], 16)))
        reg.append(int(resp[30:34], 16))
        reg.append(int(resp[34:42], 16))
        reg.append(int(resp[42:50], 16))
        reg.append(int(resp[50:58], 16))
        reg.append(int(resp[58:66], 16))
        reg.append(int(resp[66:74], 16))
        reg.append(int(resp[74:82], 16))
        carga.write(str(reg[0]) + "-" + str(reg[1]) + "-" + str(reg[2]) + "T" + str(reg[4]) + ":" + str(reg[5]) + ",")
        carga.write(str(reg[10]) + ",")
        carga.write(str(reg[11]) + ",")
        carga.write(str(reg[12]) + ",")
        carga.write(str(reg[13]) + ",")
        carga.write(str(reg[14]) + ",")
        carga.write(str(reg[15]) + ",")
        carga.write(str(reg[16]) + "\n")

carga.close()
print("Finished")
sys.exit()
