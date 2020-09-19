# Configuração do script para Smart Meter Interface (SMI)

Após abrir o web-gui do Tasmota, pelo seu IP local, deverá aceder à página de "Configuração" e "Editar Script".

Deverá ativar a opção de "script ativado" e colar o seguinte script:

Trifásico 

```
>D
 
>B
=>sensor53 r
 
>M 1
 
+1,14,m,1,9600,EB,5,50,0104006C,0104006E,01040070,01040079,0104007A,0104007F,01040026,01040028,0104000B,01040084
 
1,010404UUuuxxxx@i0:10,Tensão L1,V,Voltage_L1,16
1,010404UUuuxxxx@i1:10,Tensão L2,V,Voltage_L2,16
1,010404UUuuxxxx@i2:10,Tensão L3,V,Voltage_L3,16
1,=h&#8205;
1,010404xxxxUUuu@i0:10,Corrente L1,A,Current_L1,16
1,010404xxxxUUuu@i1:10,Corrente L2,A,Current_L2,16
1,010404xxxxUUuu@i2:10,Corrente L3,A,Current_L3,16
1,=h&#8205;
1,010408UUuuUUuuxxxxxxxxxxxx@i3:1,Potência ativa,W,Power_P1,16
1,010406xxxxxxxxUUuu@i4:1000,Fator de potência,pu,PFactor_P1,16
1,01040aUUuuxxxx@i5:10,Frequência,Hz,Frequency_P1,16
1,=h&#8205;
1,010408UUuuUUuuxxxxxxxxxxxx@i6:1000,Vazio (1),kWh,Energy_P1_R1,16
1,010408xxxxxxxxUUuuUUuuxxxx@i6:1000,Ponta (2),kWh,Energy_P1_R2,16
1,010408UUuuUUuuxxxxxxxxxxxx@i7:1000,Cheia (3),kWh,Energy_P1_R3,16
1,=h&#8205;
1,010406uuxxxxxxxx@i8:1,Tarifa,,Tariff_P1,16
1,010406uuxxxxxxxx@i9:1,DCP,,DCP_P1,16

#

```

Este script extrairá as seguintes grandesas elétricas e informações técnicas do contador inteligente, a cada 5 segundos:

* Tensão (V)
* Intensidade de corrente (A)
* Potência ativa (W)
* Frequência (Hz)
* Fator de potência (pu)
* Totalizador de energia consumida na tarifa 1 (kWh)
* Totalizador de energia consumida na tarifa 2 (kWh)
* Totalizador de energia consumida na tarifa 3 (kWh)
* Estado do Disjuntor Controlador de Potência embutido na EDP Box
  - `0` = desligado
  - `1` = ligado
  - `2` = pronto para re-ligar
* Tarifa atual
  - `1` = Vazio
  - `2` = Ponta
  - `3` = Cheia


Estes dados são pertencentes à fase Nº 1 de consumo, a única em instalações monofásicas. Para instalações trifásicas ou com produção de energia, deverá consultar a documentação citada na página principal.

Após submeter, deverá desligar e religar a alimentação do Wemos D1 mini. Posteriormente ao início da firmware, deverá obter a seguinte visualização correta, como exemplo:

![tasmota_edp_box](./img/tasmota_edp_box.png)
>


# Mais info

[Home Assistant Core e a sua configuração - Para método direto e indireto](../Home%20Assistant/README.md)

[Voltar](./README.md)
