>D

initvars="bugfix"
hh=0
mm=0
ss=0
name="EB3"
upacyr=-1
upacmt=-1
upacdy=-1
upachh=-1
upacmm=-1
upacss=-1
upacim=-1
upacex=-1

>BS

tper=60
smlj=0

=>sensor53 r

>S

if upsecs==50
then
smlj=1
endif

hh=sml[1]
mm=sml[2]
ss=sml[3]

upacyr=-1
upacmt=-1
upacdy=-1
upachh=-1
upacmm=-1
upacss=-1
upacim=-1
upacex=-1

>W

@ <b>Local Time: </b> %tstamp%
@ <b>Name: </b> %name%
@ <b>Clock: </b> %0hh%:%0mm%:%0ss%
@ <hr>

>M 1

; change to your gpios and mode
; power off is required
;  v   v             v
+1,19,mN1,0,9600,EB3,18,15,r010400010001,r0104006C0007,r010400730007,r0104007A0006,r010400260003,r010400160006,r0104000B0004,r010400800001,r010400810003,r01440601


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

1,010418UUuuUUuu@i5:1000,Total Energy Import ,kWh,TotEneImp,1
1,010418xxxxxxxxUUuuUUuu@i5:1000,Total Energy Export ,kWh,TotEneExp,3

1,=h<hr>

; 0B

1,01040euu@i6:1,Tariff ,,Tariff,16

1,=h<hr>

; 80

1,010408uu@i7:1,Config ID Byte 1 ,,*,0
1,010408xxuu@i7:1,Config ID  Byte 2 ,,*,0
1,010408xxxxuu@i7:1,Config ID Byte 3 ,,*,0
1,010408xxxxxxuu@i7:1,Config ID Byte 4 ,,*,0
1,010408xxxxxxxxuu@i7:1,Config ID Byte 5 ,,*,0
1,010408xxxxxxxxxxuu@i7:1,Config ID Byte 6 ,,*,0
1,010408xxxxxxxxxxxxuu@i7:1,Config ID Byte 7 ,,*,0
1,010408xxxxxxxxxxxxxxuu@i7:1,Config ID Byte 8 ,,*,0

; 81/82/83

1,01040cUUuuUUuu@i8:1,Capture Period ,s,*,0
1,01040cxxxxxxxxUUuuUUuu@i8:1,Entries in Use ,,*,0
1,01040cxxxxxxxxxxxxxxxxUUuuUUuu@i8:1,Profile Entries ,,*,0

1,=h<hr>
1,=hExample: lastest entry

1,01441dUUuu@i9:1,Year ,,*,0
1,01441dxxxxuu@i9:1,Month ,,*,0
1,01441dxxxxxxuu@i9:1,Day ,,*,0
1,01441dxxxxxxxxxxuu@i9:1,HH ,h,*,0
1,01441dxxxxxxxxxxxxuu@i9:1,MM ,m,*,0
1,01441dxxxxxxxxxxxxxxuu@i9:1,SS ,s,*,0
1,01441dxxxxxxxxxxxxxxxxxxUUuu@i9:1,GMT Deviation,,*,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxuu@i9:1,Summer/Winter ,,*,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxuu@i9:1,AMR Status ,,*,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i9:1000,ID 9 Import Inc ,kWh,*,3
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i9:1000,ID 9 Export Inc ,kWh,*,3

#

; eof
