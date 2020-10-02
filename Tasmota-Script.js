>D

>B

tper=60

=>sensor53 r

>M 1

+1,14,m,1,9600,EB,5,10,01040001,0104006C,0104006E,01040070,01040079,0104007B,0104007F,01040026,01040027,0104002C,01040016,0104007D,01040018,01040073,01040075,01040077,0104001A

; 01

1,010416xxxxxxxxxxxxxxuu@i0:1,Clock,s,Clock_S,16

; 6C 6E 70

1,010404UUuu@i1:10,Tensão L1,V,Voltage_L1,17
1,010404UUuu@i2:10,Tensão L2,V,Voltage_L2,17
1,010404UUuu@i3:10,Tensão L3,V,Voltage_L3,17

; 6C 6E 70

1,010404xxxxUUuu@i1:10,Corrente L1,A,Current_L1,17
1,010404xxxxUUuu@i2:10,Corrente L2,A,Current_L2,17
1,010404xxxxUUuu@i3:10,Corrente L3,A,Current_L3,17

1,=h<hr>

; 79 73 75 77

1,010408UUuuUUuu@i4:1,Potência Activa,W,Power,16
1,010408UUuuUUuu@i13:1,Potência A L1,W,Power_L1,16
1,010408UUuuUUuu@i14:1,Potência A L2,W,Power_L2,16
1,010408UUuuUUuu@i15:1,Potência A L3,W,Power_L3,16

; 7B 7F 7C

1,010404UUuu@i5:1000,Factor de Potência,pu,PFactor,19
1,010404xxxxUUuu@i5:1000,PFactor L1,pu,PFactor_L1,19
1,010404UUuu@i11:1000,PFactor L2,pu,PFactor_L2,19
1,010404xxxxUUuu@i11:1000,PFactor L3,pu,PFactor_L3,19

1,01040aUUuu@i6:10,Frequência,Hz,Frequency,1

1,=h<hr>

; 26 27 2C

1,010408UUuuUUuu@i7:1000,Consumo T1 Vazio,kWh,Energy_R1,1
1,010408UUuuUUuu@i8:1000,Consumo T2 Ponta,kWh,Energy_R2,1
1,010408xxxxxxxxUUuuUUuu@i8:1000,Consumo T3 Cheia,kWh,Energy_R3,1
1,010408UUuuUUuu@i9:1000,Consumo Total,kWh,Energy_Sum,1

; 16

1,010408xxxxxxxxUUuuUUuu@i10:1000,Energia Exportada,kWh,Energy_Export,3

; 18 1A

1,010408UUuuUUuu@i12:1000,Energia Q1,kVAr,Energy_Q1,3
1,010408xxxxxxxxUUuuUUuu@i16:1000,Energia Q4,kVAr,Energy_Q4,3

#
