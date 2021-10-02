#!/usr/bin/env python
"""
Pymodbus Synchronous Client Examples
--------------------------------------------------------------------------

The following is an example of how to use the synchronous modbus client
implementation from pymodbus.

It should be noted that the client can also be used with
the guard construct that is available in python 2.5 and up::

    with ModbusClient('127.0.0.1') as client:
        result = client.read_coils(1,10)
        print result
"""
# --------------------------------------------------------------------------- #
# import the various client implementations
# --------------------------------------------------------------------------- #
from pymodbus.client.sync import ModbusTcpClient as ModbusClient
# from pymodbus.client.sync import ModbusUdpClient as ModbusClient
# from pymodbus.client.sync import ModbusSerialClient as ModbusClient

# --------------------------------------------------------------------------- #
# configure the client logging
# --------------------------------------------------------------------------- #
import logging
FORMAT = ('%(asctime)-15s %(threadName)-15s '
          '%(levelname)-8s %(module)-15s:%(lineno)-8s %(message)s')
logging.basicConfig(format=FORMAT)
log = logging.getLogger()
log.setLevel(logging.DEBUG)

UNIT = 0x1


def run_sync_client():
    # ------------------------------------------------------------------------#
    # choose the client you want
    # ------------------------------------------------------------------------#
    # make sure to start an implementation to hit against. For this
    # you can use an existing device, the reference implementation in the tools
    # directory, or start a pymodbus server.
    #
    # If you use the UDP or TCP clients, you can override the framer being used
    # to use a custom implementation (say RTU over TCP). By default they use
    # the socket framer::
    #
    #    client = ModbusClient('localhost', port=5020, framer=ModbusRtuFramer)
    #
    # It should be noted that you can supply an ipv4 or an ipv6 host address
    # for both the UDP and TCP clients.
    #
    # There are also other options that can be set on the client that controls
    # how transactions are performed. The current ones are:
    #
    # * retries - Specify how many retries to allow per transaction (default=3)
    # * retry_on_empty - Is an empty response a retry (default = False)
    # * source_address - Specifies the TCP source address to bind to
    # * strict - Applicable only for Modbus RTU clients.
    #            Adheres to modbus protocol for timing restrictions
    #            (default = True).
    #            Setting this to False would disable the inter char timeout
    #            restriction (t1.5) for Modbus RTU
    #
    #
    # Here is an example of using these options::
    #
    #    client = ModbusClient('localhost', retries=3, retry_on_empty=True)
    # ------------------------------------------------------------------------#
    client = ModbusClient('10.3.0.232', port=9502)
    # from pymodbus.transaction import ModbusRtuFramer
    # client = ModbusClient('localhost', port=5020, framer=ModbusRtuFramer)
    # client = ModbusClient(method='binary', port='/dev/ptyp0', timeout=1)
    # client = ModbusClient(method='ascii', port='/dev/ptyp0', timeout=1)
    # client = ModbusClient(method='rtu', port='/dev/ptyp0', timeout=1,
    #                       baudrate=9600)
    client.connect()





    log.debug("Read input registers")
    rr = client.read_input_registers(1, 8, unit=UNIT)
    assert(not rr.isError())     # test that we are not an error

    
    # ----------------------------------------------------------------------- #
    # close the client
    # ----------------------------------------------------------------------- #
    client.close()


if __name__ == "__main__":
    run_sync_client()
