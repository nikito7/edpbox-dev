>D

>BS

tper=60
smlj=0

=>sensor53 r

>M 1

; change to your gpios and mode
; power off is required
;  v   v             v
+1,19,mN1,0,9600,EB99,18,15,r010400010001,r010400800001,r010400810003,r01440601


; 01

1,01040Cxxxxxxxxxxuu@i0:1,Clock ,h,Clock_H,16
1,01040Cxxxxxxxxxxxxuu@i0:1,Clock ,m,Clock_M,16
1,01040Cxxxxxxxxxxxxxxuu@i0:1,Clock ,s,Clock_S,16

1,=h<hr>

; 80

1,010408uu@i1:1,Config ID Byte 1 ,,*,0
1,010408xxuu@i1:1,Config ID  Byte 2 ,,*,0
1,010408xxxxuu@i1:1,Config ID Byte 3 ,,*,0
1,010408xxxxxxuu@i1:1,Config ID Byte 4 ,,*,0
1,010408xxxxxxxxuu@i1:1,Config ID Byte 5 ,,*,0
1,010408xxxxxxxxxxuu@i1:1,Config ID Byte 6 ,,*,0
1,010408xxxxxxxxxxxxuu@i1:1,Config ID Byte 7 ,,*,0
1,010408xxxxxxxxxxxxxxuu@i1:1,Config ID Byte 8 ,,*,0

; 81/82/83

1,01040cUUuuUUuu@i2:1,Capture Period ,s,*,0
1,01040cxxxxxxxxUUuuUUuu@i2:1,Entries in Use ,,*,0
1,01040cxxxxxxxxxxxxxxxxUUuuUUuu@i2:1,Profile Entries ,,*,0

1,=h<hr>
1,=hExample: lastest entry

1,01441dUUuu@i3:1,Year ,,*,0
1,01441dxxxxuu@i3:1,Month ,,*,0
1,01441dxxxxxxuu@i3:1,Day ,,*,0
1,01441dxxxxxxxxxxuu@i3:1,HH ,h,*,0
1,01441dxxxxxxxxxxxxuu@i3:1,MM ,m,*,0
1,01441dxxxxxxxxxxxxxxuu@i3:1,SS ,s,*,0
1,01441dxxxxxxxxxxxxxxxxxxUUuu@i3:1,GMT Deviation,,*,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxuu@i3:1,Summer/Winter ,,*,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxuu@i3:1,AMR Status ,,*,0
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i3:1000,ID 9 Import Inc ,kWh,*,3
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i3:1000,ID x ,kVAr,*,3
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i3:1000,ID x ,kVAr,*,3
1,01441dxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i3:1000,ID x Export Inc ,kWh,*,3

#

; eof
