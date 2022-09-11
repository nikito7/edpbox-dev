>D

time=""
date=""
clk=""
old=""
wfc=""
wfp=0
cnt=0

>B

=>Delay 100
=>Delay 100
=>Delay 100

tper=31
smlj=0

=>Delay 100
=>SerialLog 0
=>WifiConfig
=>WifiPower

=>Delay 100
=>Sensor53 r

>E

wfc=WifiConfig#?
wfp=WifiPower

>S

time=st(tstamp T 2)
date=st(tstamp T 1)

if cnt==40
then
smlj=1
tper=15
=>UfsRun discovery.txt
endif

>W

@<b>NTP </b> %date% %time%
@<b>Vars </b> cnt=%0cnt% tper=%0tper% smlj=%0smlj%
@<b>Vars </b> wtd=%0wtd% clk=%0clk% old=%0old%
@<b>Wifi </b> %wfc% <b> Power </b> %0wfp% <b> Topic </b> %topic%
@<br>
<br>
Tarifa {m} %ttext%

; inverter growatt

>M 1

; esp32 19/18 (hardware serial)
; esp8266 3/1 (hardware serial)
; change to your gpios and mode
; power off is required
;  v  v             v
+1,3,mN1,1,9600,PVx,1,15,r010400010001

1,=h<br>

; 6C

1,010404UUuu@i1:10,Voltage L1 ,V,Voltage,1
1,010404xxxxUUuu@i1:10,Current L1 ,A,Current,1

1,=h<br>

; 16

1,010408UUuuUUuu@i2:1000,Total Energy Import ,kWh,TEI,2
1,010408xxxxxxxxUUuuUUuu@i2:1000,Total Energy Export ,kWh,TEE,2

; eof meter

#

; escrever aqui qualquer coisa.
; ( random text )
; o tasmota nem sempre grava as alterações.
; isto confirma que o script foi gravado.
; copiar todo o script antes de salvar.

; eof script 15:26
