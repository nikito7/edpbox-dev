>D

initvars="bug fix"
hh=0
mm=0
ss=0
name="EB3"

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

>W

@ <b>Local Time:</b> %tstamp%
@ Name: %name%
@ Clock: %0hh%:%0mm%:%0ss%
@ <hr>

>M 1

; change to your gpios and mode
; power off is required 
;  v   v             v
+1,19,mN1,0,9600,EB3,18,15,r010400010001,r0104006C0007,r010400730007,r0104007A0006,r010400260003,r010400160006,r0104000B0004,r010400840003,r010400120001

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

1,010418xxxxxxxxxxxxxxxxUUuuUUuu@i5:1000,Total Energy Q1 ,kVAr,TotEneQ1,2
1,010418xxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i5:1000,Total Energy Q2 ,kVAr,TotEneQ2,3
1,010418xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i5:1000,Total Energy Q3 ,kVAr,TotEneQ3,3
1,010418xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i5:1000,Total Energy Q4 ,kVAr,TotEneQ4,2

1,=h<hr>

; 0B

1,01040euu@i6:1,Tariff ,,Tariff,16

1,01040exxUUuuUUuu@i6:1000,T1 Max Vazio ,kVA,ConT1,2
1,01040exxxxxxxxxxUUuuUUuu@i6:1000,T2 Max Ponta ,kVA,ConT2,2
1,01040exxxxxxxxxxxxxxxxxxUUuuUUuu@i6:1000,T3 Max Cheias ,kVA,ConT3,2

1,=h<hr>

; 84

1,01040auu@i7:1,ICP Status ,,ICP_Status,0
1,01040axxUUuuUUuu@i7:1,ICP Q ,,ICP_Q,0
1,01040axxxxxxxxxxUUuuUUuu@i7:1,ICP K ,%%,ICP_K,0

1,=h<hr>

; 12

1,=h<small>Potencia Contratada</small>
1,010404UUuuUUuu@i8:1000,Max Power ,kVA,Max_Power,2

1,=h<hr>

#

; eof
