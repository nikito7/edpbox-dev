>D

; EB3

bug="fix"
time=""
date=""
cnt=0
clk=0
wtd=0
old=0

>B

tper=60
smlj=0

=>Sensor53 r

>S

; delay modbus mqtt

if cnt==30
then
tper=10
smlj=1
endif

if cnt==50
then
tper=60
endif

; some vars

time=st(tstamp T 2)
date=st(tstamp T 1)

clk=sml[3]

if cnt<99
then
cnt+=1
endif

; modbus watchdog

if cnt==99
then
wtd+=1
endif

if wtd==1
then
old=sml[3]
endif

if wtd==30
then
wtd=0
if old==clk
then
=>SetSensor53 0
delay(100)
delay(100)
=>SetSensor53 1
endif
endif

>W

@<b>NTP: </b> %date% %time%
@<b>Vars: </b> cnt=%0cnt% tper=%0tper% smlj=%0smlj%
@<b>Vars: </b> wtd=%0wtd% clk=%0clk% old=%0old%
@<hr>

>M 1

; change to your gpios and mode
; power off is required
;  v  v             v
+1,3,mN1,1,9600,EB3,1,15,r010400010001,r0104006C0007,r010400730007,r0104007A0006,r010400260003,r010400160006,r0104000B0004,r01440601

; 01

1,01040Cxxxxxxxxxxuu@i0:1,Clock ,h,Clock_H,16
1,01040Cxxxxxxxxxxxxuu@i0:1,Clock ,m,Clock_M,16
1,01040Cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 6C

1,01040EUUuu@i1:10,Voltage L1 ,V,VolL1,17
1,01040ExxxxxxxxUUuu@i1:10,Voltage L2 ,V,VolL2,17
1,01040ExxxxxxxxxxxxxxxxUUuu@i1:10,Voltage L3 ,V,VolL3,17

1,=h<hr>

1,01040ExxxxxxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Current ,A,Current,17

1,01040ExxxxUUuu@i1:10,Current L1 ,A,CurL1,17
1,01040ExxxxxxxxxxxxUUuu@i1:10,Current L2 ,A,CurL2,17
1,01040ExxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Current L3 ,A,CurL3,17

1,=h<hr>

; 73

1,01041cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Active Power ,W,ActPow,16

1,01041cUUuuUUuu@i2:1,Active Power L1 ,W,ActPowL1,16
1,01041cxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Active Power L2 ,W,ActPowL2,16
1,01041cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Active Power L3 ,W,ActPowL3,16

1,=h<hr>

; 7A

1,01040eUUuuUUuu@i3:1,Active Power Export,W,ActPowExp,16

1,01040exxxxxxxxUUuu@i3:1000,Power Factor ,pu,PowFac,19
1,01040exxxxxxxxxxxxUUuu@i3:1000,Power Factor L1 ,pu,PowFacL1,19
1,01040exxxxxxxxUUuu@i3:1000,Power Factor L2 ,pu,PowFacL2,19
1,01040exxxxxxxxxxxxxxxxxxxxUUuu@i3:1000,Power Factor L3 ,pu,PowFacL3,19
1,01040exxxxxxxxxxxxxxxxxxxxxxxxUUuu@i3:10,Frequency ,Hz,Frequency,1

1,=h<hr>

; 26

1,01040CUUuuUUuu@i4:1000,Total Energy T1 Vazio ,kWh,TotEneT1,1
1,01040CxxxxxxxxUUuuUUuu@i4:1000,Total Energy T2 Ponta ,kWh,TotEneT2,1
1,01040CxxxxxxxxxxxxxxxxUUuuUUuu@i4:1000,Total Energy T3 Cheias ,kWh,TotEneT3,1

1,=h<hr>

; 16

1,010418UUuuUUuu@i5:1000,Total Energy Import ,kWh,TotEneImp,17
1,010418xxxxxxxxUUuuUUuu@i5:1000,Total Energy Export ,kWh,TotEneExp,19

1,=h<hr>

; 0B

1,01040euu@i6:1,Tariff ,,Tariff,16

1,=h<hr>

1,01441dUUuu@i7:1,Y ,,LP_Y,0
1,01441dxxxxuu@i7:1,M ,,LP_M,0
1,01441dxxxxxxuu@i7:1,D ,,LP_D,0
1,01441dxxxxxxxxxxuu@i7:1,HH ,h,LP_HH,0
1,01441dxxxxxxxxxxxxuu@i7:1,MM ,m,LP_MM,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i7:1,Import Inc ,Wh,LP_IMP,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i7:1,Export Inc ,Wh,LP_EXP,0

1,=h<hr>

#

; eof
