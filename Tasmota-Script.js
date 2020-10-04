>D

>B

tper=30

=>sensor53 r

>M 1

+1,14,m,1,9600,EB,5,8,01040001,0104006C,0104006E,01040070,01040073,01040075,01040077,01040079,0104007B,0104007D,0104007F,01040026,01040027,0104002C,01040016,01040018,0104001A

; 01

1,010416xxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

; 6C 6E 70

1,010404UUuu@i1:10,Tensão L1 ,V,Voltage_L1,17
1,010404UUuu@i2:10,Tensão L2 ,V,Voltage_L2,17
1,010404UUuu@i3:10,Tensão L3 ,V,Voltage_L3,17

1,=h<hr>

; 6C 6E 70

1,010404xxxxUUuu@i1:10,Corrente L1 ,A,Current_L1,17
1,010404xxxxUUuu@i2:10,Corrente L2 ,A,Current_L2,17
1,010404xxxxUUuu@i3:10,Corrente L3 ,A,Current_L3,17

1,=h<hr>

; 73 75 77 79

1,010408UUuuUUuu@i4:1,Potência L1 ,W,Power_L1,16
1,010408UUuuUUuu@i5:1,Potência L2 ,W,Power_L2,16
1,010408UUuuUUuu@i6:1,Potência L3 ,W,Power_L3,16
1,010408UUuuUUuu@i7:1,Potência Activa ,W,Power,16

1,=h<hr>

; 7B 7D

1,010404UUuuxxxx@i8:1000,Factor de Potência ,pu,PFactor,19
1,010404xxxxUUuu@i8:1000,PFactor L1 ,pu,PFactor_L1,19
1,010404UUuuxxxx@i9:1000,PFactor L2 ,pu,PFactor_L2,19
1,010404xxxxUUuu@i9:1000,PFactor L3 ,pu,PFactor_L3,19

; 7F

1,01040aUUuu@i10:10,Frequência ,Hz,Frequency,17

1,=h<hr>

; 26 27 2C

1,010408UUuuUUuuxxxxxxxx@i11:1000,Energia T1 Vazio ,kWh,Energy_R1,17
1,010408UUuuUUuuxxxxxxxx@i12:1000,Energia T2 Ponta ,kWh,Energy_R2,17
1,010408xxxxxxxxUUuuUUuu@i12:1000,Energia T3 Cheia ,kWh,Energy_R3,17
1,010408UUuuUUuuxxxxxxxx@i13:1000,Energia Total ,kWh,Energy_Sum,17

1,=h<hr>

; 16

1,010408xxxxxxxxUUuuUUuu@i14:1000,Energia Exportada ,kWh,Energy_Export,19

; 18 1A

1,010408UUuuUUuuxxxxxxxx@i15:1000,Energia Q1 Ri ,kVAr,Energy_Q1,19
1,010408xxxxxxxxUUuuUUuu@i16:1000,Energia Q4 Rc ,kVAr,Energy_Q4,19

#
