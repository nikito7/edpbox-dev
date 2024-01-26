>D
>B
=>sensor53 r
>M 1

+1,3,mN1,0,9600,EB99,1,15,r010400800001,r010400810003,r014503000011bc01,r0145030000000101

; 80

1,010408uu@i0:1,Config ID .1 ,,*,0
1,010408xxuu@i0:1,Config ID  .2 ,,*,0
1,010408xxxxuu@i0:1,Config ID .3 ,,*,0
1,010408xxxxxxuu@i0:1,Config ID .4 ,,*,0
1,010408xxxxxxxxuu@i0:1,Config ID .5 ,,*,0
1,010408xxxxxxxxxxuu@i0:1,Config ID .6 ,,*,0
1,010408xxxxxxxxxxxxuu@i0:1,Config ID .7 ,,*,0
1,010408xxxxxxxxxxxxxxuu@i0:1,Config ID .8 ,,*,0

; 81/82/83

1,01040cUUuuUUuu@i1:1,Capture Period ,s,*,0
1,01040cxxxxxxxxUUuuUUuu@i1:1,Entries in Use ,,*,0
1,01040cxxxxxxxxxxxxxxxxUUuuUUuu@i1:1,Profile Entries ,,*,0

1,=h<hr>
1,=hExample: newest line

1,014511UUuu@i2:1,Year ,,*,0
1,014511xxxxuu@i2:1,Month ,,*,0
1,014511xxxxxxuu@i2:1,Day ,,*,0
1,014511xxxxxxxxuu@i2:1,Week Day ,,*,0
1,014511xxxxxxxxxxuu@i2:1,Timestamp ,h,*,0
1,014511xxxxxxxxxxxxuu@i2:1,Timestamp ,m,*,0
1,014511xxxxxxxxxxxxxxuu@i2:1,Timestamp ,s,*,0
1,014511xxxxxxxxxxxxxxxxuu@i2:1,T ,hs,*,0
1,014511xxxxxxxxxxxxxxxxxxUUuu@i2:1,GMT Deviation,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxuu@i2:1,Summer/Winter ,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxxxuu@i2:1,AMR Status ,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1000,Value ID 9 ,kWh,*,3


1,=h<hr>
1,=hExample: oldest line

1,014511UUuu@i3:1,Year ,,*,0
1,014511xxxxuu@i3:1,Month ,,*,0
1,014511xxxxxxuu@i3:1,Day ,,*,0
1,014511xxxxxxxxuu@i3:1,Week Day ,,*,0
1,014511xxxxxxxxxxuu@i3:1,Timestamp ,h,*,0
1,014511xxxxxxxxxxxxuu@i3:1,Timestamp ,m,*,0
1,014511xxxxxxxxxxxxxxuu@i3:1,Timestamp ,s,*,0
1,014511xxxxxxxxxxxxxxxxuu@i3:1,T ,hs,*,0
1,014511xxxxxxxxxxxxxxxxxxUUuu@i3:1,GMT Deviation,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxuu@i3:1,Summer/Winter ,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxxxuu@i3:1,AMR Status ,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i3:1000,Value ID 9 ,kWh,*,3


1,=h<hr>

; eof M
#
; eof
