>D

time=""
date=""
cnt=0
wtd=0
clk=""
old=""
hh=0
mm=0
ss=0

>B

if upsecs<5
then
print Easy HAN: disabling wifi...
=>Wifi 0
endif

tper=15
smlj=0

=>SerialLog 0
=>SensorRetain 0
=>Sensor53 r

>S

time=st(tstamp T 2)
date=st(tstamp T 1)
hh=sml[1]
mm=sml[2]
ss=sml[3]

if cnt==5
then
print Easy HAN: enabling wifi...
=>Wifi 1
endif

if cnt==30
then
smlj=1
endif

if cnt<99
then
cnt+=1
endif

; modbus watchdog block begin

clk=s(2.0hh)+s(2.0mm)+s(2.0ss)

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
; 
; =>Restart -3
; 
endif
endif

; modbus watchdog block end

>W

@<b>NTP </b> %date% %time%
@<b>Vars </b> cnt=%0cnt% tper=%0tper% smlj=%0smlj%
@<b>Vars </b> wtd=%0wtd% clk=%0clk% old=%0old%
@<hr>

; EB1

>M 1

; esp32 19/18 (hardware serial)
; esp8266 3/1 (hardware serial)
: tfreire 14/5 (software serial)
; change to your gpios and mode
; power off is required
;  v  v             v
+1,3,mN1,1,9600,EB1,1,20,r010400010001,r0104006C0002,r010400160002,r010400260003,r010400790003,r0104007F0002,r0104000B0002

; 01

1,01040Cxxxxxxxxxxuu@i0:1,Clock ,h,CH,0
1,01040Cxxxxxxxxxxxxuu@i0:1,Clock ,m,CM,0
1,01040Cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,CS,0

1,=h<hr>

; 6C

1,010404UUuu@i1:10,Voltage L1 ,V,VL1,1
1,010404xxxxUUuu@i1:10,Current L1 ,A,CL1,1

1,=h<hr>

; 16

1,010408UUuuUUuu@i2:1000,Total Energy Import ,kWh,TEI,3
1,010408xxxxxxxxUUuuUUuu@i2:1000,Total Energy Export ,kWh,TEE,3

1,=h<hr>

; 26

1,01040CUUuuUUuu@i3:1000,Total Energy T1 Vazio ,kWh,TET1,3
1,01040CxxxxxxxxUUuuUUuu@i3:1000,Total Energy T2 Ponta ,kWh,TET2,3
1,01040CxxxxxxxxxxxxxxxxUUuuUUuu@i3:1000,Total Energy T3 Cheias ,kWh,TET3,3

1,=h<hr>

; 79

1,01040aUUuuUUuu@i4:1,Active Power Import ,W,API,0
1,01040axxxxxxxxUUuuUUuu@i4:1,Active Power Export ,W,APE,0
1,01040axxxxxxxxxxxxxxxxUUuu@i4:1000,Power Factor ,φ,PF,3

; 7F

1,01040aUUuu@i5:10,Frequency ,Hz,FR,1

; 0B

1,010406uu@i6:1,Tariff ,,Tariff,0

1,=h<hr>

#

; eof
