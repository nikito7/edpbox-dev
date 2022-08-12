>D
>B

=>SerialLog 0
=>Sensor53 r
=>Sensor53 d1

>M 1

; rx mode  baud     tx time
;  v  v     v        v  v
+1,3,mN2,1,9600,pzem,1,30,r010400000002

; console debug
;
; sensor53 d1
; sensor53 d0

1,=h<hr>

1,01040CUUuu@i0:1,go to console ,V,*,0
1,01040CxxxxUUuu@i0:1,go to console ,A,*,0

1,=h<hr>

#

; eof
