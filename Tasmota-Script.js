>D

>B

smlj=0
tper=51

->sensor53 r

>R

smlj=0

>S

if upsecs>45
then
smlj=1
endif

>M 1

+1,14,m,1,9600,EB1,5,30,r1F0400010001,r1F04006C0007,r1F0400730007,r1F04007B0005,r1F0400260003,r1F0400160002,r1F0400180004

; 01

1,1F040Cxxxxxxxxxxuu@i0:1,Clock ,h,Clock_H,16
1,1F040Cxxxxxxxxxxxxuu@i0:1,Clock ,m,Clock_M,16
1,1F040Cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 6C

1,1F040EUUuu@i1:10,Tensão L1 ,V,Voltage_L1,1
1,1F040ExxxxxxxxUUuu@i1:10,Tensão L2 ,V,Voltage_L2,1
1,1F040ExxxxxxxxxxxxxxxxUUuu@i1:10,Tensão L3 ,V,Voltage_L3,1

1,=h<hr>

1,1F040ExxxxxxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Corrente Total ,A,Current_Sum,17

1,1F040ExxxxUUuu@i1:10,Corrente L1 ,A,Current_L1,17
1,1F040ExxxxxxxxxxxxUUuu@i1:10,Corrente L2 ,A,Current_L2,17
1,1F040ExxxxxxxxxxxxxxxxxxxxUUuu@i1:10,Corrente L3 ,A,Current_L3,17

1,=h<hr>

; 73

1,1F041CxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Potência Activa ,W,Power,16

1,1F041CUUuuUUuu@i2:1,Potência L1 ,W,Power_L1,16
1,1F041CxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Potência L2 ,W,Power_L2,16
1,1F041CxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Potência L3 ,W,Power_L3,16

1,=h<hr>

; 7B

1,1F040AUUuu@i3:1000,Factor de Potência ,pu,PFactor,19
1,1F040AxxxxUUuu@i3:1000,PFactor L1 ,pu,PFactor_L1,19
1,1F040AxxxxxxxxUUuu@i3:1000,PFactor L2 ,pu,PFactor_L2,19
1,1F040AxxxxxxxxxxxxUUuu@i3:1000,PFactor L3 ,pu,PFactor_L3,19
1,1F040AxxxxxxxxxxxxxxxxUUuu@i3:10,Frequência ,Hz,Frequency,1

1,=h<hr>

; 26

1,1F040CUUuuUUuu@i4:1000,Energia T1 Vazio ,kWh,Energy_R1,1
1,1F040CxxxxxxxxUUuuUUuu@i4:1000,Energia T2 Ponta ,kWh,Energy_R2,1
1,1F040CxxxxxxxxxxxxxxxxUUuuUUuu@i4:1000,Energia T3 Cheia ,kWh,Energy_R3,1

1,=h<hr>

; 16

1,1F0408UUuuUUuu@i5:1000,Energia Importada ,kWh,Energy_Sum,1
1,1F0408xxxxxxxxUUuuUUuu@i5:1000,Energia Exportada ,kWh,Energy_Export,3

; 18

1,1F0410UUuuUUuu@i6:1000,Energia Q1 Ri ,kVAr,Energy_Q1,1
1,1F0410xxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i6:1000,Energia Q4 Rc ,kVAr,Energy_Q4,2

; dev ID: 1F

#
