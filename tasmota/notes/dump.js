>D

initvars="bugfix"
res=0
cnt=4540
end=4530
hex=""
cmd=""
sleep=0
sec=0

>BS

=>sensor53 r
=>sensor53 d1

>F

if cnt>end
and sleep==1
then
hex=hx(cnt)
cmd="014506"+hex+"01"
print dump: %0cnt% %cmd%
res=sml(1 1 cmd)
cnt-=1
endif

sleep+=1

if sleep>1
then
sleep=0
endif

>S

if cnt>end
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
