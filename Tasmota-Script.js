>D

a="xxxxxxxx"
b="xxxxxxxxxxxxxxxx"
c="xxxxxxxxxxxxxxxxxxxxxxxx"

>BS

tper=20

=>sensor53 r

>M 1

+1,14,m,1,9600,EB,5,15,r010400010001,r0104006C0007,r010400730007,r0104007B0005,r010400260003,r010400160002,r010400180004

; 01

1,01040c%a%xxuu@i0:1,Clock ,h,Clock_H,0
1,01040c%a%xxxxuu@i0:1,Clock ,m,Clock_M,16
1,01040c%a%xxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 6C

1,01040eUUuu@i1:10,Tensão L1 ,V,Voltage_L1,1
1,01040e%a%UUuu@i1:10,Tensão L2 ,V,Voltage_L2,1
1,01040e%b%UUuu@i1:10,Tensão L3 ,V,Voltage_L3,1

1,=h<hr>

1,01040e%c%UUuu@i1:10,Corrente Total ,A,Current_Sum,17

1,01040exxxxUUuu@i1:10,Corrente L1 ,A,Current_L1,17
1,01040exxxx%a%UUuu@i1:10,Corrente L2 ,A,Current_L2,17
1,01040exxxx%b%UUuu@i1:10,Corrente L3 ,A,Current_L3,17

1,=h<hr>

; 73

1,01041c%c%%c%UUuuUUuu@i2:1,Potência Activa ,W,Power,16

1,01041cUUuuUUuu@i2:1,Potência L1 ,W,Power_L1,16
1,01041c%b%UUuuUUuu@i2:1,Potência L2 ,W,Power_L2,16
1,01041c%b%%b%UUuuUUuu@i2:1,Potência L3 ,W,Power_L3,16

1,=h<hr>

; 7B

1,01040aUUuu@i3:1000,Factor de Potência ,pu,PFactor,19
1,01040axxxxUUuu@i3:1000,PFactor L1 ,pu,PFactor_L1,19
1,01040a%a%UUuu@i3:1000,PFactor L2 ,pu,PFactor_L2,19
1,01040axxxx%a%UUuu@i3:1000,PFactor L3 ,pu,PFactor_L3,19
1,01040a%b%UUuu@i3:10,Frequência ,Hz,Frequency,1

1,=h<hr>

; 26

1,01040cUUuuUUuu@i4:1000,Energia T1 Vazio ,kWh,Energy_R1,1
1,01040c%a%UUuuUUuu@i4:1000,Energia T2 Ponta ,kWh,Energy_R2,1
1,01040c%b%UUuuUUuu@i4:1000,Energia T3 Cheia ,kWh,Energy_R3,1

1,=h<hr>

; 16

1,010408UUuuUUuu@i5:1000,Energia Importada ,kWh,Energy_Sum,1
1,010408%a%UUuuUUuu@i5:1000,Energia Exportada ,kWh,Energy_Export,3

; 18

1,010410UUuuUUuu@i6:1000,Energia Q1 Ri ,kVAr,Energy_Q1,2
1,010410%c%UUuuUUuu@i6:1000,Energia Q4 Rc ,kVAr,Energy_Q4,3

; dev

#
