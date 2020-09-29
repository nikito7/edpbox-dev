>D

>BS

tper=60

=>sensor53 r

>M 1

+1,14,m,1,9600,EB,5,10,01040001,0104006C,0104006E,01040070,01040079,0104007B,0104007F,01040026,01040027,0104002C,01040016

; 01 clock
; Pseudo init fix

1,010416xxxxxxxxxxxxxxuuxx@i0:1,Clock,s,Clock_S,16

; 6C 6E 70

1,010404UUuu@i1:10,Tensão L1,V,Voltage_L1,17
1,010404UUuu@i2:10,Tensão L2,V,Voltage_L2,17
1,010404UUuu@i3:10,Tensão L3,V,Voltage_L3,17

1,=h<hr>

; 6C 6E 70

1,010404xxxxUUuu@i1:10,Corrente L1,A,Current_L1,17
1,010404xxxxUUuu@i2:10,Corrente L2,A,Current_L2,17
1,010404xxxxUUuu@i3:10,Corrente L3,A,Current_L3,17

1,=h<hr>

; 79 7B 7F

1,010408UUuuUUuu@i4:1,Potência Activa,W,Power_P1,16
1,010404UUuu@i5:1000,Factor de Potência,pu,PFactor_P1,18
1,01040aUUuu@i6:10,Frequência,Hz,Frequency_P1,1

1,=h<hr>

; 26 27 2C

1,010408UUuuUUuu@i7:1000,Consumo T1 Vazio,kWh,Energy_P1_R1,1
1,010408UUuuUUuu@i8:1000,Consumo T2 Ponta,kWh,Energy_P1_R2,1
1,010408xxxxxxxxUUuuUUuu@i8:1000,Consumo T3 Cheia,kWh,Energy_P1_R3,1
1,010408UUuuUUuu@i9:1000,Consumo Total,kWh,Energy_P1_Sum,1

; 16

1,010408xxxxxxxxUUuuUUuu@i10:1000,Energia Exportada,kWh,Energy_Export,1

#
