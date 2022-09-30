>D 40
; for external ScriptEditor
; Version see >W section
IP=192.168.178.31
; SB=6200 only if you have 1M flash
; and compile with #define EEP_SCRIPT_SIZE 6200
; and #define USE_EEPROM
SB=6200

; HowTo:
; Download the ScriptEditor from Tasmota Script page
; Change the IP and maybe the SB (look for EEP_SCRIPT_SIZE Tasmota Script page)
; change the -- SML -- script to your needs
; search for -300 und change it to your needs (I have only 300W PV) or remove it
; First start, go to console and type: script>=#dreset
; This will set the correct day consumption value
; 4h chart is not permament, after restart data is lost
; 24h, month and year chart is permament. Arrays are saved at midnight.
; to save immediately go to console and enter: script>=#save
; to change some values enter e.g.: script >dcon[day]=xxx 


; console commands:
; script?var = get variable
; script >var=1 = set variable
; script>=svars = save permament var
; script>=#sub = run sub


; -- ARRAYS --

; 24h power chart
M:p:sday=0 96

; daily energy consumption table day 1-31
M:p:dcon=0 31

; monthly energy consumption table month 1-12
M:p:mcon=0 12

; 4h power chart
M:s4h=0 960


; -- VARS --

; energy from grid [kWh]
EnFrGrid=0
; energy to grid [kWh]
EnToGrid=0
; actual power from or to grid [W]
power=0

; monthval and dayval
p:mval=0
p:dval=0

tmp=0
m15=0
cstr=""
cstr2=""
avgval=0
avgvalcnt=0
hour=0
mont=0
minutes=0



; -- BOOT --
>B

;disable mqtt at boot prevents sending 0
smlj=0

=>sensor53 r

is(0 "Jan|Feb|Mär|Apr|Mai|Jun|Jul|Aug|Sep|Okt|Nov|Dez|")

; -- SUBS --

; 24h power chart
#dreset
for tmp 1 sday[-1] 1
	sday[tmp]=0
next
svars

; daily consumption month chart
; !execute this at the first time!
#dtreset
for tmp 1 dcon[-1] 1
	dcon[tmp]=0
next
dval=EnFrGrid
svars

; monthly consumption year chart
#mtreset
for tmp 1 mcon[-1] 1
	mcon[tmp]=0
next
mval=EnFrGrid
svars

; save
#save
print saving
svars

; daily consumption month table
#daysub
wcs <div id="chartday" style="text-align:center;width:400px;height:100%%;padding:0px"></div>
wcs <script language="JavaScript">function drawChart(){
wcs var cssc={'headerRow':'hRow','rowNumberCell':'hCol','tableCell':'tCell'};
wcs var data=google.visualization.arrayToDataTable([['Tag','Verbrauch [kWh]',{role: 'style'}],
for tmp 1 dcon[-1] 1
	if (tmp<day)
	then
		wcs [%tmp%,%dcon[tmp]%,'green'],
	endif
	if (tmp==day)
	then
		wcs [%tmp%,%dcon[tmp]%,'red'],
	endif
	if (tmp>day)
	then
	    wcs [%tmp%,%dcon[tmp]%,''],
	endif
next
wcs ]);
wcs var options={chartArea:{left:40,width:'86%%'},width:'100%%',legend:'none',title:'Tagesverbräuche Monatsansicht',vAxis:{format:'# kWh'},hAxis:{title:'Tag',ticks:[1,5,10,15,20,25,30]}};
wcs var chart=new google.visualization.ColumnChart(document.getElementById('chartday'));
wcs chart.draw(data,options);}google.charts.setOnLoadCallback(drawChart);</script>

; monthly consumption year table
#monthsub
wcs <div id="chartmonth" style="text-align:center;width:400px;height:100%%;padding:0px"></div>
wcs <script language="JavaScript">function drawChart(){
wcs var cssc={'headerRow':'hRow','rowNumberCell':'hCol','tableCell':'tCell'};
wcs var data=google.visualization.arrayToDataTable([['Monat','Verbrauch [kWh]',{role: 'style'}],
for tmp 1 mcon[-1] 1
	if (tmp<month)
	then
		wcs ['%is[tmp]%',%mcon[tmp]%,'green'],
	endif
	if (tmp==month)
	then
		wcs ['%is[tmp]%',%mcon[tmp]%,'red'],
	endif
	if (tmp>month)
	then
	    wcs ['%is[tmp]%',%mcon[tmp]%,''],
	endif
next
wcs ]);
wcs var options={chartArea:{left:40,width:'86%%'},width:'100%%',legend:'none',title:'Monatsverbräuche Jahresansicht',vAxis:{format:'# kWh'}};
wcs var chart=new google.visualization.ColumnChart(document.getElementById('chartmonth'));
wcs chart.draw(data,options);}google.charts.setOnLoadCallback(drawChart);</script>

; random array
#rnddcon
for tmp 1 dcon[-1] 1
	dcon[tmp]=rnd(10)
next



;-- SML --
>M 1
;1=meter1 14=GPIO14 s=SML 0=filterOff 9600=baud MT175=Name 
+1,14,s,16,9600,MT175
1,77070100010800ff@1000,Verbrauch,KWh,Total_in,2
1,77070100020800ff@1000,Netzeinspeisung,KWh,Total_out,2
1,77070100100700ff@1,Leistung,W,Power_curr,0



; -- EVERY SECOND --
>S

hour=hours
mont=month

; get SML values, every teleperiod (10s)!
if (upsecs%tper==0)
then
    smlj=1
	; energy from grid [kWh]
	EnFrGrid=sml[1]
	; energy to grid [kWh]
	EnToGrid=sml[2]
	; actual power [W]
	power=sml[3]
	; day consumption [kWh]
	dcon[day]=EnFrGrid-dval
	; month consumption [kWh]
	mcon[month]=EnFrGrid-mval
	; MQTT
	;=>publish tele/%topic%/SENSOR {"Time":"%tstamp%","MT175":{"daily_con":%2dcon[day]%,"monthly_con":%2mcon[month]%}}
endif


; 4h power chart - every 15s
if (secs%15==0)
then
	; power to array, idx is set automatically
	s4h=power
	; sum up power for "24h chart"
	avgval+=power
	avgvalcnt+=1;	
endif
; set x axis index to 4 hours a 15 sec therefore /240, no decimal point
hour-=4
if (hour<0)
then
	cstr2="cnth"+s(1.0((24-4+hours)*240)+(mins*4))+"/240"
else
	cstr2="cnth"+s(1.0((hours-4)*240)+(mins*4))+"/240"
endif
hour=hours


; 24h power chart
; calc avg power [W] for last 15min and put into array[1-96]
m15=int((((hours*60)+mins)/15)+1)
if ((mins%15==0) and (chg[m15]>0))
then
	sday[m15]=int(avgval/avgvalcnt)
	avgval=0
	avgvalcnt=0
	;svars save too often will damage flash
endif
; set idx (pointer starts from 0!!)
sday[0]=m15-1
; set x axis idx to 24 hours a 15 min therefore /4, no decimal point
; calc minutes for x-axis
tmp=hours
if (mins<45)
then
	minutes=mins+15	
else
	minutes=mins-45
	if (tmp<23)
	then
		tmp+=1
	else
		tmp=0
	endif
endif
cstr="cnt"+s(1.0(tmp+(int(minutes/15)/4))*4)+"/4"


; day consumption calculation at midnight
if ((chg[hour]>0) and (hour==0))
then
    print Its midnight
	dval=EnFrGrid
	; month change?
	if (chg[mont]>0)
	then
		mval=EnFrGrid
	endif
	; save only 1 at midnight
    svars	
endif



; WEB INTERFACE
>W
; Auto reload
;$<script> setTimeout("location.reload(true);",5000); </script>

; consumption
Tagesverbrauch:{m}%2(EnFrGrid-dval)% kWh
Monatsverbrauch:{m}%2(EnFrGrid-mval)% kWh

; Time/Date
Datum:{m}%s(2.0day)%.%s(2.0month)%.%s(2.0year)% - %s(2.0hours)%:%s(2.0mins)%:%s(2.0secs)%
Uptime:{m}%0uptime% min

; 4h power chart
$<div id="chart1" style="text-align:center;width:400px;height:100%%;padding:0px"></div>
$gc(lt s4h "wr" "Leistung [W]" cstr2)
$var options = {
$chartArea:{left:60,width:'83%%'},
$width:'100%%',
$legend:'none',
$vAxis:{format:'# W',viewWindow:{min:-300}},
$explorer:{actions:['dragToZoom', 'rightClickToReset']},
$title:'Verbrauch 4 Stunden [Watt]'
$};
$gc(e)

; 24h power chart
$<div id="chart2" style="text-align:center;width:400px;height:100%%;padding:0px"></div>
$gc(lt sday "wr" "Leistung [W]" cstr)
$var options = {
$chartArea:{left:60,width:'83%%'},
$width:'100%%',
$legend:'none',
$vAxis:{format:'# W',viewWindow:{min:-300}},
$explorer:{actions:['dragToZoom', 'rightClickToReset']},
$title:'Verbrauch 24 Stunden [Watt]'
$};
$gc(e)

; monthly energy consumption year chart
%=#daysub

; monthly energy consumption year chart
%=#monthsub

$<center><span style="font-size:10px;">
$Version 2022.09.27<br>
$free heap: %s(0.0heap)% bytes<br>
$Hinweis: Die Daten werden immer um Mitternacht gespeichert!<br>
$Sofort speichern dies in Console eingeben: "script>=#save"<br>
$</span></center>

; -- END SCRIPT --
#
