>D

time=""
date=""
clk=""
old=""
wfc=""
cnt=0
wtd=0
mm=0
ss=0

>BS

tper=20
smlj=0

=>SerialLog 0
=>SensorRetain 0
=>Sensor53 r
=>WifiConfig

>E

wfc=WifiConfig#?

>S

time=st(tstamp T 2)
date=st(tstamp T 1)
mm=sml[2]
ss=sml[3]

if cnt==30
then
smlj=1
tper=15
endif

if cnt<99
then
cnt+=1
endif

; modbus watchdog block begin

clk=s(2.0mm)+s(2.0ss)

if cnt==99
then
wtd+=1
endif

if wtd==1
then
old=clk
endif

if wtd==90
then
wtd=0
if old==clk
then
print Easy HAN: modbus error !!!
print Easy HAN: modbus error !!!
print Easy HAN: modbus error !!!
; 
=>Restart -3
; 
endif
endif

; modbus watchdog block end

>W

@NTP: %date% %time%
@Vars: cnt=%0cnt% tper=%0tper% smlj=%0smlj%
@Vars: wtd=%0wtd% clk=%0clk% old=%0old%
@Wifi: %wfc%
@<br>

; Below registers only work in EB3 !

>M 1

; esp32 19/18 (hardware serial)
; esp8266 3/1 (hardware serial)
: tfreire 14/5 (software serial)
; change to your gpios and mode
; power off is required
;  v  v             v
+1,3,mN1,1,9600,EB3,1,20,r010400010001,r0104006C0007,r010400730007,r0104007A0006,r010400260003,r010400160006,r0104000B0004,r01440601

; 01

1,01040Cxxxxxxxxxxuu@i0:1,Clock,h,CH,0
1,01040Cxxxxxxxxxxxxuu@i0:1,Clock,m,CM,0
1,01040Cxxxxxxxxxxxxxxuu@i0:1,Clock,s,CS,0

1,=h<br>

; 6C

1,01040EUUuu@i1:10,Voltage L1,V,VL1,1
1,01040ExxxxxxxxUUuu@i1:10,Voltage L2,V,VL2,1
1,01040ExxxxxxxxxxxxxxxxUUuu@i1:10,Voltage L3,V,VL3,1

1,=h<br>

1,01040ExxxxxxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Current Total,A,CT,1

1,01040ExxxxUUuu@i1:10,Current L1,A,CL1,1
1,01040ExxxxxxxxxxxxUUuu@i1:10,Current L2,A,CL2,1
1,01040ExxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Current L3,A,CL3,1

1,=h<br>

; 73

1,01041cx8x8x8UUuuUUuu@i2:1,Active Power Import,W,API,0

1,01041cUUuuUUuu@i2:1,Active Power L1,W,API1,0
1,01041cx8UUuuUUuu@i2:1,Active Power L2,W,API2,0
1,01041cx8x8UUuuUUuu@i2:1,Active Power L3,W,API3,0

1,01041cx4UUuuUUuu@i2:1,Active Power L1 Export,W,APE1,0
1,01041cx8x4UUuuUUuu@i2:1,Active Power L2 Export,W,APE2,0
1,01041cx8x8x4UUuuUUuu@i2:1,Active Power L3 Export,W,APE3,0

1,=h<br>

; 7A

1,01040eUUuuUUuu@i3:1,Active Power Export,W,APE,0

1,01040exxxxxxxxUUuu@i3:1000,Power Factor,φ,PF,3
1,01040exxxxxxxxxxxxUUuu@i3:1000,Power Factor L1,φ,PF1,3
1,01040exxxxxxxxxxxxxxxxUUuu@i3:1000,Power Factor L2,φ,PF2,3
1,01040exxxxxxxxxxxxxxxxxxxxUUuu@i3:1000,Power Factor L3,φ,PF3,3
1,01040exxxxxxxxxxxxxxxxxxxxxxxxUUuu@i3:10,Frequency,Hz,FR,1

1,=h<br>

; 26

1,01040CUUuuUUuu@i4:1000,Total Energy T1 Vazio,kWh,TET1,1
1,01040CxxxxxxxxUUuuUUuu@i4:1000,Total Energy T2 Ponta,kWh,TET2,1
1,01040CxxxxxxxxxxxxxxxxUUuuUUuu@i4:1000,Total Energy T3 Cheias,kWh,TET3,1

1,=h<br>

; 16

1,010418UUuuUUuu@i5:1000,Total Energy Import,kWh,TEI,1
1,010418xxxxxxxxUUuuUUuu@i5:1000,Total Energy Export,kWh,TEE,3

1,=h<br>

; 0B

1,01040euu@i6:1,Tariff,,Tariff,0

; load profile

1,=h<br>Load Profile (15min)<br>
1,=h<br>

1,01441dUUuu@i7:1,Year,,LPY,0
1,01441dxxxxuu@i7:1,Month,,LPM,0
1,01441dxxxxxxuu@i7:1,Day,,LPD,0
1,01441dxxxxxxxxxxuu@i7:1,Hour,h,LPHH,0
1,01441dxxxxxxxxxxxxuu@i7:1,Minute,m,LPMM,0

1,01441dxxx4x8UUuuUUuu@i7:1,Import Inc,Wh,LPIMP,0
1,01441dxxx4x8xxxxxxxxUUuuUUuu@i7:1,+Ri Inc,VArh,*,0
1,01441dxxx4x8xxxxxxxxxxxxxxxxUUuuUUuu@i7:1,-Rc Inc,VArh,*,0

1,01441dxxx4x8x8xxxxxxxxxxxxxxxxUUuuUUuu@i7:1,Export Inc,Wh,LPEXP,0
1,01441dxxx4x8x8xxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i7:1,R3 Inc,VArh,*,0
1,01441dxxx4x8x8xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i7:1,R4 Inc,VArh,*,0

; eof load profile

; eof meter

#

; eof script
