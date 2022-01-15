>D

; EB1 mono

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

if cnt==30
then
tper=10
smlj=1
endif

if cnt==50
then
tper=60
endif

time=st(tstamp T 2)
date=st(tstamp T 1)

if cnt<99
then
cnt+=1
endif

; modbus watchdog

clk=sml[3]

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
print modbus error
; 
=>Restart -3
; 
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
;   v  v             v
+1,19,mN1,1,9600,EB1,19,15,r010400010001,r0104006C0002,r010400160002,r010400260003,r010400790003,r0104007F0002,r0104000B0002,r0104002D0003,r01440601

; import: r01440301
; import+export: r01440601

; 01

1,01040Cxxxxxxxxxxuu@i0:1,Clock ,h,Clock_H,16
1,01040Cxxxxxxxxxxxxuu@i0:1,Clock ,m,Clock_M,16
1,01040Cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 6C

1,010404UUuu@i1:10,Voltage L1 ,V,VolL1,17
1,010404xxxxUUuu@i1:10,Current L1 ,A,CurL1,17

1,=h<hr>

; 16

1,010408UUuuUUuu@i2:1000,Total Energy Import ,kWh,TotEneImp,1
1,010408xxxxxxxxUUuuUUuu@i2:1000,Total Energy Export ,kWh,TotEneExp,1

1,=h<hr>

; 26

1,01040CUUuuUUuu@i3:1000,Total Energy T1 Vazio ,kWh,TotEneT1,1
1,01040CxxxxxxxxUUuuUUuu@i3:1000,Total Energy T2 Ponta ,kWh,TotEneT2,1
1,01040CxxxxxxxxxxxxxxxxUUuuUUuu@i3:1000,Total Energy T3 Cheias ,kWh,TotEneT3,1

1,=h<hr>

; 79

1,01040aUUuuUUuu@i4:1,Active Power ,W,ActPow,16
1,01040axxxxxxxxUUuuUUuu@i4:1,Active Power Export ,W,ActPowExp,16
1,01040axxxxxxxxxxxxxxxxUUuu@i4:1000,Power Factor ,pu,PowFac,19

; 7F

1,01040aUUuu@i5:10,Frequency ,Hz,Frequency,2

; 0B

1,010406uu@i6:1,Tariff ,,Tariff,0

1,=h<hr>

; 2D

1,01040CUUuuUUuu@i7:1000,Total Energy T1 Export ,kWh,TotEneT1Exp,3
1,01040CxxxxxxxxUUuuUUuu@i7:1000,Total Energy T2 Export ,kWh,TotEneT2Exp,3
1,01040CxxxxxxxxxxxxxxxxUUuuUUuu@i7:1000,Total Energy T3 Export ,kWh,TotEneT3Exp,3

1,=h<hr>

; import: 11
; import+export: 1d

1,01441dUUuu@i8:1,Y ,,LP_Y,0
1,01441dxxxxuu@i8:1,M ,,LP_M,0
1,01441dxxxxxxuu@i8:1,D ,,LP_D,0
1,01441dxxxxxxxxxxuu@i8:1,HH ,h,LP_HH,0
1,01441dxxxxxxxxxxxxuu@i8:1,MM ,m,LP_MM,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i8:1000,Import Inc ,kWh,LP_IMP,3

1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i8:1000,Export Inc ,kWh,LP_EXP,3

#

; eof
