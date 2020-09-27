>D

>BS

tper=60

=>sensor53 r

>M 1

+1,14,m,1,9600,EB,5,15,0104006C,0104006E,01040070,01040079,0104007B,0104007F,01040026,01040027,0104002C,0104000B,0104005C,01040001

; 6C 6E 70

1,010404UUuu@i0:10,Tensão L1,V,Voltage_L1,1
1,010404UUuu@i1:10,Tensão L2,V,Voltage_L2,1
1,010404UUuu@i2:10,Tensão L3,V,Voltage_L3,1

1,=h<hr>

; 6C 6E 70

1,010404xxxxUUuu@i0:10,Corrente L1,A,Current_L1,17
1,010404xxxxUUuu@i1:10,Corrente L2,A,Current_L2,17
1,010404xxxxUUuu@i2:10,Corrente L3,A,Current_L3,17

1,=h<hr>

; 79 7B 7F 5C

1,010408UUuuUUuu@i3:1,Potência Activa,W,Power_P1,16
1,010410UUuuUUuu@i10:1,Potência Pico Média,W,Power_Max_P1,0
1,010404UUuu@i4:1000,Factor de Potência,pu,PFactor_P1,18
1,01040aUUuu@i5:10,Frequência,Hz,Frequency_P1,1

1,=h<hr>

; 26 27 2C 0B

1,010408UUuuUUuu@i6:1000,Consumo Vazio T1,kWh,Energy_P1_R1,1
1,010408UUuuUUuu@i7:1000,Consumo Ponta T2,kWh,Energy_P1_R2,1
1,010408xxxxxxxxUUuuUUuu@i7:1000,Consumo Cheia T3,kWh,Energy_P1_R3,1
1,010408UUuuUUuu@i8:1000,Consumo Total,kWh,Energy_P1_Sum,1
1,010406uu@i9:1,Tarifa Activa,,Tariff_P1,16

1,=h<hr>

; 01

1,010416xxxxxxxxxxuu@i11:1,Clock,h,Clock_H,0
1,010416xxxxxxxxxxxxuu@i11:1,Clock,m,Clock_M,16
1,010416xxxxxxxxxxxxxxuu@i11:1,Clock,s,Clock_S,16

#
