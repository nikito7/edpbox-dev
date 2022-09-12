>D

time=""
date=""
wfc=""
wfp=0
cnt=0

>B

=>Delay 100
=>Delay 100
=>Delay 100

tper=31
smlj=0

=>Delay 100
=>SerialLog 0
=>WifiConfig
=>WifiPower

=>Delay 100
=>Sensor53 r

>E

wfc=WifiConfig#?
wfp=WifiPower

>S

time=st(tstamp T 2)
date=st(tstamp T 1)

if cnt==40
then
smlj=1
tper=15
=>UfsRun discovery.txt
endif

if cnt<99
then
cnt+=1
endif

>W

@<b>NTP </b> %date% %time%
@<b>Vars </b> cnt=%0cnt% tper=%0tper% smlj=%0smlj%
@<b>Wifi </b> %wfc% <b> Power </b> %0wfp% <b> Topic </b> %topic%
@<br>

; inverter growatt

>M 1

; esp32 19/18 (hardware serial)
; esp8266 3/1 (hardware serial)
; change to your gpios and mode
; power off is required
;  v  v             v
+1,3,mN1,1,9600,PVx,1,15,r010400000002,r010400370002

; 0x0000

1,010404xxuu@i0:1,Inverter Status,,*,0

; 55-56 0x0037

1,010404UUuuUUuu@i1:10,Total Energy,kWh,PV_Energy,1

; eof meter

#

; eof script 14:57

