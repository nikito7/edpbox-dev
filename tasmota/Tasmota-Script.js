>D

>BS

smlj=0
tper=30

->sensor53 r

>R

smlj=0

>S

if upsecs>20
then
smlj=1
endif

>M 1

+1,14,m,1,9600,EB1,5,10,r010400010001,r0104006C0007,r010400730007,r0104007B0005,r010400260003,r010400160006

; 01

1,01040Cxxxxxxxxxxuu@i0:1,Clock ,h,Clock_H,16
1,01040Cxxxxxxxxxxxxuu@i0:1,Clock ,m,Clock_M,16
1,01040Cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 6C

1,01040EUUuu@i1:10,Voltage L1 ,V,Voltage_L1,1
1,01040ExxxxxxxxUUuu@i1:10,Voltage L2 ,V,Voltage_L2,1
1,01040ExxxxxxxxxxxxxxxxUUuu@i1:10,Voltage L3 ,V,Voltage_L3,1

1,=h<hr>

1,01040ExxxxxxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Current ,A,Current,17

1,01040ExxxxUUuu@i1:10,Current L1 ,A,Current_L1,17
1,01040ExxxxxxxxxxxxUUuu@i1:10,Current L2 ,A,Current_L2,17
1,01040ExxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Current L3 ,A,Current_L3,17

1,=h<hr>

; 73

1,01041cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Active Power ,W,Active_Power,16

1,01041cUUuuUUuu@i2:1,Active Power L1 ,W,Active_Power_L1,16
1,01041cxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Active Power L2 ,W,Active_Power_L2,16
1,01041cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Active Power L3 ,W,Active_Power_L3,16

1,=h<hr>

; 7B

1,01040AUUuu@i3:1000,Power Factor ,pu,Power_Factor,19
1,01040AxxxxUUuu@i3:1000,Power Factor L1 ,pu,Power_Factor_L1,19
1,01040AxxxxxxxxUUuu@i3:1000,Power Factor L2 ,pu,Power_Factor_L2,19
1,01040AxxxxxxxxxxxxUUuu@i3:1000,Power Factor L3 ,pu,Power_Factor_L3,19
1,01040AxxxxxxxxxxxxxxxxUUuu@i3:10,Frequency ,Hz,Frequency,1

1,=h<hr>

; 26

1,01040CUUuuUUuu@i4:1000,Total Energy T1 Vazio ,kWh,Total_Energy_T1,1
1,01040CxxxxxxxxUUuuUUuu@i4:1000,Total Energy T2 Ponta ,kWh,Total_Energy_T2,1
1,01040CxxxxxxxxxxxxxxxxUUuuUUuu@i4:1000,Total Energy T3 Cheia ,kWh,Total_Energy_T3,1

1,=h<hr>

; 16

1,010418UUuuUUuu@i5:1000,Total Energy Import ,kWh,Total_Energy_Import,1
1,010418xxxxxxxxUUuuUUuu@i5:1000,Total Energy Export ,kWh,Total_Energy_Export,3
1,010418xxxxxxxxxxxxxxxxUUuuUUuu@i5:1000,Total Energy Q1 ,kVAr,Total_Energy_Q1,1
1,010418xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i5:1000,Total Energy Q4 ,kVAr,Total_Energy_Q4,2

; dev

#
