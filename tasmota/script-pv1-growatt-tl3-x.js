>D

bug="fix"
wfc=""
wfp=0
cnt=0

>B

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

@<b>Vars </b> cnt=%0cnt% tper=%0tper% smlj=%0smlj%
@<b>Wifi </b> %wfc% <b> Power </b> %0wfp% <b> Topic </b> %topic%
@<br>

; inverter growatt tl3-x

>M 1

+1,3,mN1,1,9600,PVx,1,15,r010400000002,r010400370002,r0104005D0003

; 0x0000

1,010404xxuu@i0:1,Inverter Status,,PV_Status,0

; 55-56 0x0037

1,010404UUuuUUuu@i1:10,Total Energy,kWh,PV_Energy,1

1,=h<br>

; 93-95 0x005D

1,010406UUuu@i2:10,Temp 1,°C,*,1
1,010406xxxxUUuu@i2:10,Temp 2,°C,*,1
1,010406xxxxxxxxUUuu@i2:10,Temp 3,°C,*,1

; eof meter

#

; eof script 
; check code 14:31

