>D

initvars="bugfix"
res=0
cnt=4100
hex=""
cmd=""
sec=0

>BS

=>sensor53 r
=>sensor53 d1

>F

if cnt>3000
then
hex=hx(cnt)
cmd="014506"+hex+"01"
print dump: %0cnt% %cmd%
res=sml(1 1 cmd)
cnt-=1
endif

>S

if cnt>3000
then
sec+=1
endif

>W

@ <b>Local Time: </b> %tstamp%
@ <b>Dump: </b> %0cnt%
@ <b>Elapsed: </b> %0sec%s
@ <hr> 

>M 1
+1,19,mN1,0,9600,EB99,18
#
; eof
