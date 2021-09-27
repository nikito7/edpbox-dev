>D
>B
=>sensor53 r
>M 1

+1,19,mN1,0,9600,EB99,18,15,r010400800001,r010400810003,014509000011bc01

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
1,=hExample:

1,014511UUuu@i2:1,Year ,,*,0

1,014511xxxxxxxxxxuu@i2:1,Timestamp ,h,*,0
1,014511xxxxxxxxxxxxuu@i2:1,Timestamp ,m,*,0
1,014511xxxxxxxxxxxxxxuu@i2:1,Timestamp ,s,*,0

1,014511xxxxxxxxxxxxxxxxxxxxxxuu@i2:1,Clock Status ,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxxxuu@i2:1,AMR Status ,,*,0
1,014511xxxxxxxxxxxxxxxxxxxxxxxxxxUUuuUUuu@i2:1000,value ,kWh,*,0


1,=h<hr>

; eof M
#
; eof
