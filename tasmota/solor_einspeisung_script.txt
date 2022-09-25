>D 40
IP=192.168.188.61
SB=2560:1535
;Globalvariablen werden im ganzen WLAN sichtbar
; total Einspeisung
g:sedt=0
; momentane Einspeisung
g:sedc=0

; 24*7 Wochengrafik
M:p:sold=0 168
; letzter total Wert
p:sel=0

; 24 Stunden Tagesgrafik
M:p:sday=0 96
p:dsel=0

;Tagesertrag 1 Woche Tabelle
M:p:tweek=0 7
p:mval=0

hr=0
tmp=0
m15=0
cstr=""
wd=0
itmr=0

; beim Booten
>B
; restart des SML Treibers
=>sensor53 r
smlj=0

; lösche change flag
m15=int(hours*60+mins/15+1)
tmp=chg[m15]

; diese Subroutine löscht das permanente Array
; und damit die Grafik
; kann via Konsole aufgerufen werden
; script>=#reset
#reset
for tmp 1 sold[-1] 1
	sold[tmp]=0
next
sel=sedt
svars

; das gleiche für die Tagesgrafik
#dreset
for tmp 1 sday[-1] 1
	sday[tmp]=0
next
dsel=sedt
svars

; das gleiche für die Tabelle
#treset
for tmp 1 tweek[-1] 1
	tweek[tmp]=0
next
mval=sedt
svars

; jede Sekunde
>S

itmr+=1
if itmr>30
then
	smlj=1
endif


; setze Glabalvariablen aus SML
; alle Teleperiod Sekunden
if upsecs%tper==0
then
	; totale Einspeisung
	sedt=sml[1]
	; momentane Einspeisung
	sedc=sml[2]
endif

; alle 15 Minuten ein  Wert in Tagesgrafik
; Wert geht von 1-96
m15=int(hours*60+mins/15+1)
if chg[m15]>0
then
	if sedt>0
	and dsel>0
	then
		; Wert ins Array, hier Watt statt KWh
		sday[m15]=sedt-dsel*4000
		dsel=sedt
		; permanente Variablen speichern
		svars
		print 15 minute save %m15%
	endif
endif
sday[0]=m15

; setzt x Achsen index auf 24 Stunden a 15 Minuten
; deshalb /4, keine Nachkommastellen
dp0
cstr="cnt"+s(hours*4)+"/4"
dp2

; jede Stunde eine Woche ein Wert ins Array für Grafik
; Wert geht von 0-167
hr=wday-1*24+hours
if chg[hr]>0
then
	if hours==0
	then
		; Mitternacht
		if sedt>0
		then
			; Tagesertrag für 1 Woche
			tmp=wday-1
			if tmp==0
			then
				tmp=7
			endif
			tweek[tmp]=sedt-mval
			mval=sedt
		endif
	endif
	

	; wir brauchen die vergangene Stunde, also -1
	tmp=hr-1
	; Unterlauf prüfen
	if tmp<0
	then
		tmp=167
	endif
	; Wert ins Array, hier Watt statt KWh
	if sedt>0
	and sel>0
	then
		;Werte für eine Woche jede Stunde 
		sold[tmp+1]=sedt-sel*1000
		sel=sedt
		; permanente Variablen speichern
		svars
		print one hour save %tmp%
	endif
endif

; tabellenindex setzen
tweek[0]=wday-1

; index des Wochen Arrays setzen damit Grafik zeitsynchron
sold[0]=hr

; sende email in der Nacht vom Samstag um Mitternacht
wd=wday
if chg[wd]>0
and wd==1
then
	=>sendmail [*:*:*:*:*:<mrx@googlemail.com>:Wochenbericht]*
endif

; email text
>m
Dacheinspeisung (So-Sa) in KWh vom %tstamp%
%2tweek[1]%, %2tweek[2]%, %2tweek[3]%, %2tweek[4]%, %2tweek[5]%, %2tweek[6]%, %2tweek[7]%

&tweek

; web interface
>W

;Tagesertrag:{m}<span style="color:green;">%2(sedt-mval)% kWh</span>
Tagesertrag:{m}<span style="color:green;">%2(sedt)% kWh</span>

#
<br>
; Fenster für Graph 1 definieren
$<div id="chart1"style="width:640px;height:300px;margin:0 auto"></div>
; Liniengrafik 7 Tage a 24 Stunden definieren
; diese Zeile generiert das Array wie von Google Charts benötigt
$gc(lt sold "wr" "DE"  "So|Mo|Di|Mi|Do|Fr|Sa")
; diese Zeilen definieren Grafik Optionen (siehe Google Chart Doku)
$var options = {
$vAxis:{viewWindow:{min:0,max:5000},title: 'Watt'},
$hAxis: {title: 'Wochenverlauf'},
$title:'Dacheinspeisung 1 Woche'
$};
; diese Zeile beendet die Google Chart Definition
$gc(e)

; Fenster für Graph 2 definieren
$<div id="chart2"style="width:640px;height:300px;margin:0 auto"></div>
;Liniengrafik 24 Stunden
$gc(lt  sday "wr" "DE" cstr)
$var options = {
$vAxis:{viewWindow:{min:0,max:5000},title: 'Watt'},
$hAxis: {title: 'Tagesverlauf'},
$title:'Dacheinspeisung 24 Stunden'
$};
$gc(e)

; Fenster für Graph 3 = Tabelle definieren
$<br><div id="chart3"style="width:640px;height:200px;margin:0 auto"></div><br>
; Tabelle für Tagesertrag 1 Woche hier ohne Options
$gc(t tweek "Tag" "Dacheinspeisung kWh" "So|Mo|Di|Mi|Do|Fr|Sa" "")

;1-0:2.8.1*255(12.34)

; OBIS Einspeisezähler (nur Einspeisung)
>M 1
+1,3,o,0,115200,OBIS
-1,1-0:2.8.1*255(@1+100,Einspeisung,KWh,Total_out,4
-1,=d 1 10 @1,Aktuelle Einspeisung,W,Power_curr,0
-1,1-0:0.0.0*255(@#),Zähler Nr,,Meter_number,0
#
