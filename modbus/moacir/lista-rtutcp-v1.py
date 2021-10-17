#!/usr/bin/python3

# load all necessary modules
import socket
import crcmod
import time
import sys

# create register command list
cmd_04 = [

# This command description and expected values have been defined in the EDP publication DEF-C44-509/N
#####################################################################################################

# Index  Field name                                                               Type         Unit    Scaler
[   '0', "",                                                                      "",          "",     ""   ],
[   '1', "clock",                                                                 "clock",     "-",    "-"  ],
[   '2', "Device ID 1 - Device Serial Number",                                    "octet",     "-",    "-"  ],
[   '3', "Device ID 2 - Manufacturer Model Codes and Year",                       "octet",     "-",    "-"  ],
[   '4', "Active core firmware Id.",                                              "octet",     "-",    "-"  ],
[   '5', "Active app firmware Id.",                                               "octet",     "-",    "-"  ],
[   '6', "Active com firmware Id.",                                               "octet",     "-",    "-"  ],
[   '7', "HAN interface - Modbus address",                                        "unsigned",  "-",    "-"  ],
[   '8', "HAN interface - Access profile",                                        "bitString", "-",    "-"  ],
[   '9', "Status control",                                                        "octet",     "-",    "-"  ],
[  '10', "Activity Calendar - Active Name",                                       "octet",     "-",    "-"  ],
[  '11', "Currently active tariff",                                               "unsigned",  "-",    "-"  ],
[  '12', "Active demand control threshold T1",                                    "double",    "VA",   "0"  ],
[  '13', "Active demand control threshold T2",                                    "double",    "VA",   "0"  ],
[  '14', "Active demand control threshold T3",                                    "double",    "VA",   "0"  ],
[  '15', "Active demand control threshold T4",                                    "double",    "VA",   "0"  ],
[  '16', "Active demand control threshold T5",                                    "double",    "VA",   "0"  ],
[  '17', "Active demand control threshold T6",                                    "double",    "VA",   "0"  ],
[  '18', "Currently apparent power threshold",                                    "double",    "VA",   "0"  ],
[  '19', "Demand management status",                                              "Demand",    "-",    "-"  ],
[  '20', "Demand management period definition",                                   "Demand",    "-",    "-"  ],
[  '21', "Residual power threshold",                                              "double",    "VA",   "0"  ],
[  '22', "Active energy import (+A)",                                             "double",    "Wh",   "0"  ],
[  '23', "Active energy export (-A)",                                             "double",    "Wh",   "0"  ],
[  '24', "Reactive energy QI (+Ri)",                                              "double",    "VArh", "0"  ],
[  '25', "Reactive energy QII (+Rc)",                                             "double",    "VArh", "0"  ],
[  '26', "Reactive energy QIII (-Ri)",                                            "double",    "VArh", "0"  ],
[  '27', "Reactive energy QIV (-Rc)",                                             "double",    "VArh", "0"  ],
[  '28', "Active energy import (+A) L1",                                          "double",    "Wh",   "0"  ],
[  '29', "Active energy import (+A) L2",                                          "double",    "Wh",   "0"  ],
[  '30', "Active energy import (+A) L3",                                          "double",    "Wh",   "0"  ],
[  '31', "Active energy export (-A) L1",                                          "double",    "Wh",   "0"  ],
[  '32', "Active energy export (-A) L2",                                          "double",    "Wh",   "0"  ],
[  '33', "Active energy export (-A) L3",                                          "double",    "Wh",   "0"  ],
[  '34', "Max demand active power + (QI+QIV)",                                    "double",    "W",    "0"  ],
[  '35', "Max demand active power + (QI+QIV) (capture time)",                     "clock",     "-",    "-"  ],
[  '36', "Max demand active power - (QII+QIII)",                                  "double",    "W",    "0"  ],
[  '37', "Max demand active power - (QII+QIII) (capture time)",                   "clock",     "-",    "-"  ],
[  '38', "Rate 1 contract 1 active energy (+A)",                                  "double",    "Wh",   "0"  ],
[  '39', "Rate 2 contract 1 active energy (+A)",                                  "double",    "Wh",   "0"  ],
[  '40', "Rate 3 contract 1 active energy (+A)",                                  "double",    "Wh",   "0"  ],
[  '41', "Rate 4 contract 1 active energy (+A)",                                  "double",    "Wh",   "0"  ],
[  '41', "Rate 5 contract 1 active energy (+A)",                                  "double",    "Wh",   "0"  ],
[  '43', "Rate 6 contract 1 active energy (+A)",                                  "double",    "Wh",   "0"  ],
[  '44', "Total Rate contract 1 active energy (+A)",                              "double",    "Wh",   "0"  ],
[  '45', "Rate 1 contract 1 active energy (-A)",                                  "double",    "Wh",   "0"  ],
[  '46', "Rate 2 contract 1 active energy (-A)",                                  "double",    "Wh",   "0"  ],
[  '47', "Rate 3 contract 1 active energy (-A)",                                  "double",    "Wh",   "0"  ],
[  '48', "Rate 4 contract 1 active energy (-A)",                                  "double",    "Wh",   "0"  ],
[  '49', "Rate 5 contract 1 active energy (-A)",                                  "double",    "Wh",   "0"  ],
[  '50', "Rate 6 contract 1 active energy (-A)",                                  "double",    "Wh",   "0"  ],
[  '51', "Total Rate contract 1 active energy (-A)",                              "double",    "Wh",   "0"  ],
[  '52', "Rate 1 contract 1 reactive energy QI (+Ri)",                            "double",    "VArh", "0"  ],
[  '53', "Rate 2 contract 1 reactive energy QI (+Ri)",                            "double",    "VArh", "0"  ],
[  '54', "Rate 3 contract 1 reactive energy QI (+Ri)",                            "double",    "VArh", "0"  ],
[  '55', "Rate 4 contract 1 reactive energy QI (+Ri)",                            "double",    "VArh", "0"  ],
[  '56', "Rate 5 contract 1 reactive energy QI (+Ri)",                            "double",    "VArh", "0"  ],
[  '57', "Rate 6 contract 1 reactive energy QI (+Ri)",                            "double",    "VArh", "0"  ],
[  '58', "Total Rate contract 1 reactive energy QI (+Ri)",                        "double",    "VArh", "0"  ],
[  '59', "Rate 1 contract 1 reactive energy QII (+Rc)",                           "double",    "VArh", "0"  ],
[  '60', "Rate 2 contract 1 reactive energy QII (+Rc)",                           "double",    "VArh", "0"  ],
[  '61', "Rate 3 contract 1 reactive energy QII (+Rc)",                           "double",    "VArh", "0"  ],
[  '62', "Rate 4 contract 1 reactive energy QII (+Rc)",                           "double",    "VArh", "0"  ],
[  '63', "Rate 5 contract 1 reactive energy QII (+Rc)",                           "double",    "VArh", "0"  ],
[  '64', "Rate 6 contract 1 reactive energy QII (+Rc)",                           "double",    "VArh", "0"  ],
[  '65', "Total Rate contract 1 reactive energy QII (+Rc)",                       "double",    "VArh", "0"  ],
[  '66', "Rate 1 contract 1 reactive energy QIII (-Ri)",                          "double",    "VArh", "0"  ],
[  '67', "Rate 2 contract 1 reactive energy QIII (-Ri)",                          "double",    "VArh", "0"  ],
[  '68', "Rate 3 contract 1 reactive energy QIII (-Ri)",                          "double",    "VArh", "0"  ],
[  '69', "Rate 4 contract 1 reactive energy QIII (-Ri)",                          "double",    "VArh", "0"  ],
[  '70', "Rate 5 contract 1 reactive energy QIII (-Ri)",                          "double",    "VArh", "0"  ],
[  '71', "Rate 6 contract 1 reactive energy QIII (-Ri)",                          "double",    "VArh", "0"  ],
[  '72', "Total Rate contract 1 reactive energy QIII (-Ri)",                      "double",    "VArh", "0"  ],
[  '73', "Rate 1 contract 1 reactive energy QIV (-Rc)",                           "double",    "VArh", "0"  ],
[  '74', "Rate 2 contract 1 reactive energy QIV (-Rc)",                           "double",    "VArh", "0"  ],
[  '75', "Rate 3 contract 1 reactive energy QIV (-Rc)",                           "double",    "VArh", "0"  ],
[  '76', "Rate 4 contract 1 reactive energy QIV (-Rc)",                           "double",    "VArh", "0"  ],
[  '77', "Rate 5 contract 1 reactive energy QIV (-Rc)",                           "double",    "VArh", "0"  ],
[  '78', "Rate 6 contract 1 reactive energy QIV (-Rc)",                           "double",    "VArh", "0"  ],
[  '79', "Total Rate contract 1 reactive energy QIV (-Rc)",                       "double",    "VArh", "0"  ],
[  '80', "Rate 1 contract 1 Maximum demand active power + (last average)",        "double",    "W",    "0"  ],
[  '81', "Rate 1 contract 1 Maximum demand active power + (capture time)",        "clock",     "-",    "-"  ],
[  '82', "Rate 2 contract 1 Maximum demand active power + (last average)",        "double",    "W",    "0"  ],
[  '83', "Rate 2 contract 1 Maximum demand active power + (capture time)",        "clock",     "-",    "-"  ],
[  '84', "Rate 3 contract 1 Maximum demand active power + (last average)",        "double",    "W",    "0"  ],
[  '85', "Rate 3 contract 1 Maximum demand active power + (capture time)",        "clock",     "-",    "-"  ],
[  '86', "Rate 4 contract 1 Maximum demand active power + (last average)",        "double",    "W",    "0"  ],
[  '87', "Rate 4 contract 1 Maximum demand active power + (capture time)",        "clock",     "-",    "-"  ],
[  '88', "Rate 5 contract 1 Maximum demand active power + (last average)",        "double",    "W",    "0"  ],
[  '89', "Rate 5 contract 1 Maximum demand active power + (capture time)",        "clock",     "-",    "-"  ],
[  '90', "Rate 6 contract 1 Maximum demand active power + (last average)",        "double",    "W",    "0"  ],
[  '91', "Rate 6 contract 1 Maximum demand active power + (capture time)",        "clock",     "-",    "-"  ],
[  '92', "Total Rate contract 1 Maximum demand active power + (last average)",    "double",    "W",    "0"  ],
[  '93', "Total Rate contract 1 Maximum demand active power + (capture time)",    "clock",     "-",    "-"  ],
[  '94', "Rate 1 contract 1 Maximum demand active power - (last average)",        "double",    "W",    "0"  ],
[  '95', "Rate 1 contract 1 Maximum demand active power - (capture time)",        "clock",     "-",    "-"  ],
[  '96', "Rate 2 contract 1 Maximum demand active power - (last average)",        "double",    "W",    "0"  ],
[  '97', "Rate 2 contract 1 Maximum demand active power - (capture time)",        "clock",     "-",    "-"  ],
[  '98', "Rate 3 contract 1 Maximum demand active power - (last average)",        "double",    "W",    "0"  ],
[  '99', "Rate 3 contract 1 Maximum demand active power - (capture time)",        "clock",     "-",    "-"  ],
[ '100', "Rate 4 contract 1 Maximum demand active power - (last average)",        "double",    "W",    "0"  ],
[ '101', "Rate 4 contract 1 Maximum demand active power - (capture time)",        "clock",     "-",    "-"  ],
[ '102', "Rate 5 contract 1 Maximum demand active power - (last average)",        "double",    "W",    "0"  ],
[ '103', "Rate 5 contract 1 Maximum demand active power - (capture time)",        "clock",     "-",    "-"  ],
[ '104', "Rate 6 contract 1 Maximum demand active power - (last average)",        "double",    "W",    "0"  ],
[ '105', "Rate 6 contract 1 Maximum demand active power - (capture time)",        "clock",     "-",    "-"  ],
[ '106', "Total Rate contract 1 Maximum demand active power - (last average)",    "double",    "W",    "0"  ],
[ '107', "Total Rate contract 1 Maximum demand active power - (capture time)",    "clock",     "-",    "-"  ],
[ '108', "Instantaneous Voltage L1",                                              "long",      "V",    "-1" ],
[ '109', "Instantaneous Current L1",                                              "long",      "A",    "-1" ],
[ '110', "Instantaneous Voltage L2",                                              "long",      "V",    "-1" ],
[ '111', "Instantaneous Current L2",                                              "long",      "A",    "-1" ],
[ '112', "Instantaneous Voltage L3",                                              "long",      "V",    "-1" ],
[ '113', "Instantaneous Current L3",                                              "long",      "A",    "-1" ],
[ '114', "Instantaneous Current (Sum of all phases)",                             "long",      "A",    "-1" ],
[ '115', "Instantaneous Active power + L1",                                       "double",    "W",    "0"  ],
[ '116', "Instantaneous Active power - L1",                                       "double",    "W",    "0"  ],
[ '117', "Instantaneous Active power + L2",                                       "double",    "W",    "0"  ],
[ '118', "Instantaneous Active power - L2",                                       "double",    "W",    "0"  ],
[ '119', "Instantaneous Active power + L3",                                       "double",    "W",    "0"  ],
[ '120', "Instantaneous Active power - L3",                                       "double",    "W",    "0"  ],
[ '121', "Instantaneous Active power + (Sum of all phases)",                      "double",    "W",    "0"  ],
[ '122', "Instantaneous Active power - (Sum of all phases)",                      "double",    "W",    "0"  ],
[ '123', "Instantaneous Power factor",                                            "long",      "-",    "-3" ],
[ '124', "Instantaneous Power factor L1",                                         "long",      "-",    "-3" ],
[ '125', "Instantaneous Power factor L2",                                         "long",      "-",    "-3" ],
[ '126', "Instantaneous Power factor L3",                                         "long",      "-",    "-3" ],
[ '127', "Instantaneous Frequency",                                               "long",      "Hz",   "-1" ],
[ '128', "Load profile - Configured measurements",                                "Array",     "-",    "-"  ],
[ '129', "Load profile - Capture period",                                         "double",    "s",    "0"  ],
[ '130', "Load profile - Entries in use",                                         "double",    "-",    "-"  ],
[ '131', "Load profile - Profile entries",                                        "double",    "-",    "-"  ],
[ '132', "disconnect control state",                                              "disconnect","-",    "-"  ],
[ '133', "disconnector Q parameter",                                              "double",    "-",    "-"  ],
[ '134', "disconnector K parameter",                                              "double",    "%",    "0"  ],
[ '135', "Reactive energy QI (+Ri) L1",                                           "double",    "Wh",   "0"  ],
[ '136', "Reactive energy QI (+Ri) L2",                                           "double",    "Wh",   "0"  ],
[ '137', "Reactive energy QI (+Ri) L3",                                           "double",    "Wh",   "0"  ],
[ '138', "Reactive energy QII (+Rc) L1",                                          "double",    "Wh",   "0"  ],
[ '139', "Reactive energy QII (+Rc) L2",                                          "double",    "Wh",   "0"  ],
[ '140', "Reactive energy QII (+Rc) L3",                                          "double",    "Wh",   "0"  ],
[ '141', "Reactive energy QIII (-Ri) L1",                                         "double",    "Wh",   "0"  ],
[ '142', "Reactive energy QIII (-Ri) L2",                                         "double",    "Wh",   "0"  ],
[ '143', "Reactive energy QIII (-Ri) L3",                                         "double",    "Wh",   "0"  ],
[ '144', "Reactive energy QIV (-Rc) L1",                                          "double",    "Wh",   "0"  ],
[ '145', "Reactive energy QIV (-Rc) L2",                                          "double",    "Wh",   "0"  ],
[ '146', "Reactive energy QIV (-Rc) L3",                                          "double",    "Wh",   "0"  ],
[ '147', "Max demand active power + (QI+QIV) L1",                                 "double",    "W",    "0"  ],
[ '148', "Max demand active power + (QI+QIV) L1 (capture time)",                  "clock",     "-",    "-"  ],
[ '149', "Max demand active power + (QI+QIV) L2",                                 "double",    "W",    "0"  ],
[ '150', "Max demand active power + (QI+QIV) L2 (capture time)",                  "clock",     "-",    "-"  ],
[ '151', "Max demand active power + (QI+QIV) L3",                                 "double",    "W",    "0"  ],
[ '152', "Max demand active power + (QI+QIV) L3 (capture time)",                  "clock",     "-",    "-"  ],
[ '153', "Max demand active power - (QII+QIII) L1",                               "double",    "W",    "0"  ],
[ '154', "Max demand active power - (QII+QIII) L1 (capture time)",                "clock",     "-",    "-"  ],
[ '155', "Max demand active power - (QII+QIII) L2",                               "double",    "W",    "0"  ],
[ '156', "Max demand active power - (QII+QIII) L2 (capture time)",                "clock",     "-",    "-"  ],
[ '157', "Max demand active power - (QII+QIII) L3",                               "double",    "W",    "0"  ],
[ '158', "Max demand active power - (QII+QIII) L3 (capture time)",                "clock",     "-",    "-"  ],
[ '159', "Total Rate contract 1 Maximum demand active power + L1 (last average)", "double",    "W",    "0"  ],
[ '160', "Total Rate contract 1 Maximum demand active power + L1 (capture time)", "clock",     "-",    "-"  ],
[ '161', "Total Rate contract 1 Maximum demand active power + L2 (last average)", "double",    "W",    "0"  ],
[ '162', "Total Rate contract 1 Maximum demand active power + L2 (capture time)", "clock",     "-",    "-"  ],
[ '163', "Total Rate contract 1 Maximum demand active power + L3 (last average)", "double",    "W",    "0"  ],
[ '164', "Total Rate contract 1 Maximum demand active power + L3 (capture time)", "clock",     "-",    "-"  ],
[ '165', "Total Rate contract 1 Maximum demand active power - L1 (last average)", "double",    "W",    "0"  ],
[ '166', "Total Rate contract 1 Maximum demand active power - L1 (capture time)", "clock",     "-",    "-"  ],
[ '167', "Total Rate contract 1 Maximum demand active power - L2 (last average)", "double",    "W",    "0"  ],
[ '168', "Total Rate contract 1 Maximum demand active power - L2 (capture time)", "clock",     "-",    "-"  ],
[ '169', "Total Rate contract 1 Maximum demand active power - L3 (last average)", "double",    "W",    "0"  ],
[ '170', "Total Rate contract 1 Maximum demand active power - L3 (capture time)", "clock",     "-",    "-"  ],
[ '171', "Instantaneous Apparent power + (QI+QIV) L1",                            "double",    "VA",   "0"  ],
[ '172', "Instantaneous Apparent power - (QII+QIII) L1",                          "double",    "VA",   "0"  ],
[ '173', "Instantaneous Apparent power + (QI+QIV) L2",                            "double",    "VA",   "0"  ],
[ '174', "Instantaneous Apparent power - (QII+QIII) L2",                          "double",    "VA",   "0"  ],
[ '175', "Instantaneous Apparent power + (QI+QIV) L3",                            "double",    "VA",   "0"  ],
[ '176', "Instantaneous Apparent power - (QII+QIII) L3",                          "double",    "VA",   "0"  ],
[ '177', "Instantaneous Apparent power + (QI+QIV) (Sum of all phases)",           "double",    "VA",   "0"  ],
[ '178', "Instantaneous Apparent power - (QII+QIII) (Sum of all phases)",         "double",    "VA",   "0"  ],
[ '179', "Maximum Apparent Power per phase (S PMF )",                             "double",    "VA",   "0"  ],
[ '180', "Duration of long power failures in all phases",                         "double",    "s",    "0"  ],
[ '181', "Duration of long power failures in phase L1",                           "double",    "s",    "0"  ],
[ '182', "Duration of long power failures in phase L2",                           "double",    "s",    "0"  ],
[ '183', "Duration of long power failures in phase L3",                           "double",    "s",    "0"  ],
[ '184', "Duration of long power failures in any phase",                          "double",    "s",    "0"  ],
[ '185', "Number of long power failures in all phases",                           "long",      "-",    "-"  ],
[ '186', "Number of long power failures in phase L1",                             "long",      "-",    "-"  ],
[ '187', "Number of long power failures in phase L2",                             "long",      "-",    "-"  ],
[ '188', "Number of long power failures in phase L3",                             "long",      "-",    "-"  ],
[ '189', "Number of long power failures in any phase",                            "long",      "-",    "-"  ],
[ '190', "Number of undervoltages in any phase",                                  "long",      "-",    "-"  ],
[ '191', "Duration of undervoltages in any phase",                                "double",    "s",    "0"  ],
[ '192', "Number of undervoltages in phase L1 1",                                 "long",      "-",    "-"  ],
[ '193', "Duration of undervoltages in phase L1 1",                               "double",    "s",    "0"  ],
[ '194', "Number of undervoltages in phase L2 1",                                 "long",      "-",    "-"  ],
[ '195', "Duration of undervoltages inphase L2 1",                                "double",    "s",    "0"  ],
[ '196', "Number of undervoltages in phase L3 1",                                 "long",      "-",    "-"  ],
[ '197', "Duration of undervoltages in phase L3 1",                               "double",    "s",    "0"  ],
[ '198', "Number of undervoltages for average voltage in all 3 phases 1",         "long",      "-",    "-"  ],
[ '199', "Duration of undervoltages for average voltage in all 3 phases 1",       "double",    "s",    "0"  ],
[ '200', "Number of overvoltages in any phase",                                   "long",      "-",    "-"  ],
[ '201', "Duration of overvoltagess in any phase",                                "double",    "s",    "0"  ],
[ '202', "Number of overvoltages in phase L1 1",                                  "long",      "-",    "-"  ],
[ '203', "Duration of overvoltages in phase L1 1",                                "double",    "s",    "0"  ],
[ '204', "Number of overvoltages in phase L2 1",                                  "long",      "-",    "-"  ],
[ '205', "Duration of overvoltages in phase L2 1",                                "double",    "s",    "0"  ],
[ '206', "Number of overvoltages in phase L3 1",                                  "long",      "-",    "-"  ],
[ '207', "Duration of overvoltages in phase L3 1",                                "double",    "s",    "0"  ],
[ '208', "Number of overvoltages for average voltage in all 3 phases 1",          "long",      "-",    "-"  ],
[ '209', "Duration of overvoltages for average voltage in all 3 phases 1",        "double",    "s",    "0"]]

# configure CRC calculation
crc16 = crcmod.mkCrcFun(0x18005, rev=True, initCrc=0xFFFF, xorOut=0x0000)

############################################################
HOST = '172.16.7.37' # The remote host
PORT = 3000          # The port to connect to
ser = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ser.connect((HOST, PORT))
############################################################

# function to add CRC to command
def add_crc(data):
    # get CRC and return it in hex with 4 digits
    crc = "0x{:04x}".format((crc16(bytearray.fromhex(data))))
    return(data + crc[4:6] + crc[2:4])

# function to get registers
def get_data(data):
    cmd = bytearray.fromhex(add_crc(data))  # add CRC to the command
    get = True                              # main loop, get data
    while get:
        ser.sendall(cmd)    # write request to serial
        time.sleep(0.5)                     # wait a while before reading modbus response...
        resp = ser.recv(1).hex()            # read 1 byte from serial
        found = False
        while found == False:               # search for requested response
            c = 0                           # counter to prevent loops
            while resp != data[0:2]:        # check if response comes from the slave you request data
                resp = ser.recv(1).hex()    # if not, keep reading serial buffer
                c += 1                      # prevent looping forever
                if c == 32:                 # after reading 32 bytes break the loop if not found
                    break                   # break inner loop
            if c == 32:                     # check if got the loop limit
                break                       # breal outer loop and send command again, restarting the process

            resp = resp + ser.recv(1).hex() # found slave number response corret so add the comand and check it
            if resp == data[0:4]:           # break the loop if the response includes the requested sent command
                found = True                # found it, set the variable to break the main loop
            else:

                if resp == data[0:2] + "c5":        # response was an error, expose exception code
                    resp = resp + ser.recv(1).hex() # so get the error number
                    error = ""
                    x = resp[4:6]
                    if x == "01":
                        error = "Illigal function."
                    if x == "02":
                        error = "Illigal address."
                    if x == "03":
                        error = "Illigal data values."
                    if x == "04":
                        error = "Slave device failure."
                    if x == "81":
                        error = "Access denied."
                    if x == "82":
                        error = "Measurement does not exist."
                    if x == "83":
                        error = "Entry does not exist."
                    if x == "84":
                        error = "Data to retrieve exceeded."

                    ser.close()
                    sys.exit("\nError: " + error + "\n")

                resp == ser.recv(1).hex()          # was not an error, reset response buffer and start reading from serial again
        if found == True:                          # slave and command response were ok, continue
            resp = resp + ser.recv(1).hex()        # get how many bytes are there to retrieve
            get_more = int(resp[4:6], 16) + 2      # set the number of additional bytes to read and do it, includding CRC
            resp = resp + ser.recv(get_more).hex() # get the remaining data
            crc = crc16(bytearray.fromhex(resp))   # check CRC response sanity
            if crc == 0:                           # check if CRC is ok
                get = False                        # If ok, break the main get data loop and return data

    ser.close()                                    # close serial port
    return(resp)                                   # return colected response

if len(sys.argv) == 1 or len(sys.argv) > 2:
    print("Help")
    sys.exit(-1)

# get the register to be read from command line
cmd = int(sys.argv[1])

if cmd < 0 or cmd > 209:
    sys.exit("\nThe register number is out of range.\n")

# define the kind of requested data
name_   = cmd_04[cmd][1]              # get register name
type_   = cmd_04[cmd][2]              # get register type
unit_   = cmd_04[cmd][3]              # get register unity
scaler_ = cmd_04[cmd][4]              # get register scale

if scaler_ != "-":                    # if there is a scaler, then process it
    base_   = 10 ** abs(int(scaler_)) # get the number of decimal places
    if base_ == 0:                    # Avoid division by zero
        base_ = 1

# print initial data about the request
print("\nRegister: " + "{:0>3d}".format(cmd) + " (" + "0x{:04x}".format(cmd) + ")")
print("Name:     " + name_)
print("Type:     " + type_ + "   " + "Unity: " + unit_ + "   " + "Scaler: " + scaler_)

# build hex command to be sent over serial port
hex_cmd = "0104" + "{:04x}".format(cmd) + "0001"

resp = get_data(hex_cmd)   # get data
reg  = []                  # set array to receive extrated data

# process data based on byte size/type
######################################

# if long
if type_ == "long":        # process long size
    reg.append(int(resp[6:10],  16))

# if double
if type_ == "double":      # process double size
    reg.append(int(resp[6:14],  16))

# if clock
if type_ == "clock":       # process clock
    reg.append(int(resp[6:10],  16)) # reg-0  Year
    reg.append(int(resp[10:12], 16)) # reg-1  Month
    reg.append(int(resp[12:14], 16)) # reg-2  Day
    reg.append(int(resp[14:16], 16)) # reg-3  weekday
    reg.append(int(resp[16:18], 16)) # reg-4  Hour
    reg.append(int(resp[18:20], 16)) # reg-5  Mimutes
    reg.append(int(resp[20:22], 16)) # reg-6  Seconds
    reg.append(int(resp[22:24], 16)) # reg-7  Hunderds of seconds
    reg.append(int(resp[24:28], 16)) # reg-8  Deviation from local to GMT
    reg.append(int(resp[28:30], 16)) # reg-9  Clock status (0x0* Winter; 0x8* Summer; 0FF not specified)

    if reg[8] == 32768:     # process GMT
        reg[8] = "Not specified"
    else: reg[8] = str(reg[8])

    if reg[9]  < 8:         # process season
        reg[9] = "Winter"
    if reg[9]  > 7:
        reg[9] = "Summer"
    if reg[9]  == 255:
        reg[9] = "Not epecified"

    print("Date: " + str(reg[0]) + "-" + str(reg[1]) + "-" + str(reg[2]))
    print("Time: " + str(reg[4]) + ":" + str(reg[5]) + ":" + str(reg[6]))
    print("GMT distance: " + reg[8])
    print("Weekday: " + str(reg[3]) + "\nClock status: " + reg[9])
    sys.exit(0)

if type_ == "unsigned":    # process unsigned
    reg.append(int(resp[6:8],  16))

######## TO BE DONE ###########################
if type_ == "disconnect":  # process disconnect
    print("Sorry! This script is not yet prepared to process this kind of response...")
    sys.exit()

if type_ == "octet":       # process octect
    print("Sorry! This script is not yet prepared to process this kind of response...")
    print("Anyway, your request was: " + hex_cmd + " and the response was: " + resp)
    sys.exit()

if type_ == "bitString":   # process bitString
    print("Sorry! This script is not yet prepared to process this kind of response...")
    sys.exit()
######## END OF TO BE DONE ####################

# prepare for generic printing results
######################################

if scaler_ != "-":         # if there is a scaler
    reg[0] = reg[0]/base_  # apply scaler

if unit_ == "-":           # if there is no unity, remove "-" from it
    unit_ = ""

# print generic data
print("Value: " + str(reg[0]) + unit_ + "\n")

sys.exit(0)
