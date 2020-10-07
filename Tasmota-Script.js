>D

>BS

; clock ha 20s update

tper=20

=>sensor53 r

>M 1

+1,14,m,1,9600,EB,5,11,r010400010001,r0104006C0007,r010400730007,r0104007B0005,r010400260003,r0104002C0001,r010400170001,r010400180004

; 0104-0001-0001

1,01040cxxxxxxxxxxuu@i0:1,Clock ,h,Clock_H,16
1,01040cxxxxxxxxxxxxuu@i0:1,Clock ,m,Clock_M,16
1,01040cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 0104-006C-0007

1,01040eUUuu@i1:10,Tensão L1 ,V,Voltage_L1,16
1,01040exxxxxxxxUUuu@i1:10,Tensão L2 ,V,Voltage_L2,16
1,01040exxxxxxxxxxxxxxxxUUuu@i1:10,Tensão L3 ,V,Voltage_L3,16

1,=h<hr>

1,01040exxxxxxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Corrente Total ,A,Current_Sum,17

1,01040exxxxUUuu@i1:10,Corrente L1 ,A,Current_L1,17
1,01040exxxxxxxxxxxxUUuu@i1:10,Corrente L2 ,A,Current_L2,17
1,01040exxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Corrente L3 ,A,Current_L3,17

1,=h<hr>

; 0104-0073-0007

1,01041cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Potência Activa ,W,Power,16

1,01041cUUuuUUuu@i2:1,Potência L1 ,W,Power_L1,16
1,01041cxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Potência L2 ,W,Power_L2,16
1,01041cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Potência L3 ,W,Power_L3,16

1,=h<hr>

; 0104-007B-0005

1,01040aUUuu@i3:1000,Factor de Potência ,pu,PFactor,19
1,01040axxxxUUuu@i3:1000,PFactor L1 ,pu,PFactor_L1,19
1,01040axxxxxxxxUUuu@i3:1000,PFactor L2 ,pu,PFactor_L2,19
1,01040axxxxxxxxxxxxUUuu@i3:1000,PFactor L3 ,pu,PFactor_L3,19
1,01040axxxxxxxxxxxxxxxxUUuu@i3:10,Frequência ,Hz,Frequency,17

1,=h<hr>

; 0104-0026-0003

1,01040cUUuuUUuu@i4:1000,Energia T1 Vazio ,kWh,Energy_R1,17
1,01040cxxxxxxxxUUuuUUuu@i4:1000,Energia T2 Ponta ,kWh,Energy_R2,17
1,01040cxxxxxxxxxxxxxxxxUUuuUUuu@i4:1000,Energia T3 Cheia ,kWh,Energy_R3,17

; 0104-002C-0001

1,010404UUuuUUuu@i5:1000,Energia Total ,kWh,Energy_Sum,17

1,=h<hr>

; 0104-0017-0001

1,010404UUuuUUuu@i6:1000,Energia Exportada ,kWh,Energy_Export,19

; 0104-0018-0004

1,010410UUuuUUuu@i7:1000,Energia Q1 Ri ,kVAr,Energy_Q1,18
1,010410xxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i7:1000,Energia Q4 Rc ,kVAr,Energy_Q4,19

#
