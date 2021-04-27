>D

; EB2 mono

>BS

smlj=0
tper=90

=>sensor53 r

>S

if upsecs==50
then
smlj=1
endif

->LedPower 2

print script: up %upsecs%

>M 1

; change to your gpios and mode
;  v   v             v
+1,18,mN2,1,9600,EB2,19,30,r010400010001,r0104006C0007,r010400730007,r0104007B0005,r010400260003,r010400160006

; 01

1,01040Cxxxxxxxxxxuu@i0:1,Clock ,h,Clock_H,16
1,01040Cxxxxxxxxxxxxuu@i0:1,Clock ,m,Clock_M,16
1,01040Cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 6C

1,01040EUUuu@i1:10,Voltage L1 ,V,VolL1,17

1,01040ExxxxxxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Current ,A,Current,17

1,01040ExxxxUUuu@i1:10,Current L1 ,A,CurL1,17

; 73

1,01041cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Active Power ,W,ActPow,16

1,01041cUUuuUUuu@i2:1,Active Power L1 ,W,ActPowL1,16

1,=h<hr>

; 7B

1,01040AUUuu@i3:1000,Power Factor ,pu,PowFac,19
1,01040AxxxxUUuu@i3:1000,Power Factor L1 ,pu,PowFacL1,19
1,01040AxxxxxxxxxxxxxxxxUUuu@i3:10,Frequency ,Hz,Frequency,1

1,=h<hr>

; 26

1,01040CUUuuUUuu@i4:1000,Total Energy T1 Vazio ,kWh,TotEneT1,1
1,01040CxxxxxxxxUUuuUUuu@i4:1000,Total Energy T2 Ponta ,kWh,TotEneT2,1
1,01040CxxxxxxxxxxxxxxxxUUuuUUuu@i4:1000,Total Energy T3 Cheia ,kWh,TotEneT3,1

1,=h<hr>

; 16

1,010418UUuuUUuu@i5:1000,Total Energy Import ,kWh,TotEneImp,2
1,010418xxxxxxxxUUuuUUuu@i5:1000,Total Energy Export ,kWh,TotEneExp,3

#

; eof
