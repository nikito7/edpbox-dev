>D

initvars="bugfix"
hex=""
cmd=""
date=""
time=""
res=0
sleep=0
sec=0
cnt=0
now=0
begin=4550
end=0

>B

cnt=begin

=>sensor53 d1
=>sensor53 r

>F

if cnt>end
and sleep==1
then
now=cnt
hex=hx(cnt)
cmd="014506"+hex+"01"
res=sml(1 1 cmd)
cnt-=1
endif

sleep+=1

if sleep>1
then
sleep=0
endif

>S

time=st(tstamp T 2)
date=st(tstamp T 1)

if cnt>end
then
sec+=1
endif

>W

@ <b>Local: </b> %date% %time%
@ <b>Begin: </b> %0begin% lines
@ <b>Now: </b> %0cnt% lines
@ <b>End: </b> %0end% lines
@ <b>Elapsed: </b> %0sec%s
@ <hr> 

>M 1
+1,3,mN1,0,9600,Dump,1
#
; eof
