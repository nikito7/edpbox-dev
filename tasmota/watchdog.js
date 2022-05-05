clk=sml[3]

if cnt==99
then
wtd+=1
endif

if wtd==1
then
old=sml[3]
endif

if wtd==50
then
wtd=0
if old==clk
then
print modbus error
; 
=>Restart -3
; 
endif
endif
