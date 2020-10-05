>D

>BS

tper=60

=>sensor53 r

>M 1

+1,14,m,1,9600,EB,5,15,01040001,r0104006C0006,,,01040079,01040073,01040075,01040077,r0104007B0005,,,r010400260003,0104002C,01040016,01040018,0104001A

; 01

1,010416xxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 0104-006C-0006

1,01040CUUuu@i1:10,Tensão L1 ,V,Voltage_L1,16
1,01040CxxxxxxxxUUuu@i1:10,Tensão L2 ,V,Voltage_L2,16
1,01040CxxxxxxxxxxxxxxxxUUuu@i1:10,Tensão L3 ,V,Voltage_L3,16

1,01040CxxxxUUuu@i1:10,Corrente L1 ,A,Current_L1,17
1,01040CxxxxxxxxxxxxUUuu@i1:10,Corrente L2 ,A,Current_L2,17
1,01040CxxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Corrente L3 ,A,Current_L3,17


1,=h<hr>

; 79 73 75 77

1,010408UUuuUUuu@i4:1,Potência Activa ,W,Power,16
1,010408UUuuUUuu@i5:1,Potência L1 ,W,Power_L1,16
1,010408UUuuUUuu@i6:1,Potência L2 ,W,Power_L2,16
1,010408UUuuUUuu@i7:1,Potência L3 ,W,Power_L3,16

1,=h<hr>

; 0104-007B-0005

1,01040aUUuu@i8:1000,Factor de Potência ,pu,PFactor,18
1,01040axxxxUUuu@i8:1000,PFactor L1 ,pu,PFactor_L1,18
1,01040axxxxxxxxUUuu@i8:1000,PFactor L2 ,pu,PFactor_L2,18
1,01040axxxxxxxxxxxxUUuu@i8:1000,PFactor L3 ,pu,PFactor_L3,18
1,01040axxxxxxxxxxxxxxxxUUuu@i8:10,Frequência ,Hz,Frequency,17

1,=h<hr>

; 0104-0026-0003

1,01040cUUuuUUuu@i11:1000,Energia T1 Vazio ,kWh,Energy_R1,16
1,01040cxxxxxxxxUUuuUUuu@i11:1000,Energia T2 Ponta ,kWh,Energy_R2,16
1,01040cxxxxxxxxxxxxxxxxUUuuUUuu@i11:1000,Energia T3 Cheia ,kWh,Energy_R3,16

; 2C

1,010408UUuuUUuu@i12:1000,Energia Total ,kWh,Energy_Sum,16

1,=h<hr>

; 16

1,010408xxxxxxxxUUuuUUuu@i13:1000,Energia Exportada ,kWh,Energy_Export,19

; 18 1A

1,010408UUuuUUuuxxxxxxxx@i14:1000,Energia Q1 +Ri ,kVAr,Energy_Q1,19
1,010408xxxxxxxxUUuuUUuu@i15:1000,Energia Q4 -Rc ,kVAr,Energy_Q4,19

; dev

#
