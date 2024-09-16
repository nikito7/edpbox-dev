title esptool
@echo off
echo.
echo erase flash
echo.
esptool erase_flash
echo.
echo write flash
echo.
esptool -b 921600 write_flash 0x0 tasmota32c6.factory.bin 0x3b0000 littlefs-esp32.bin
echo.
title done flash
rem EOF %time%
pause


