# Configuração do Home Assistant Core

# Método indireto

## Ficheiro de configuração

Deverá transpôr o conteúdo do ficheiro [configuration.yaml](./configuration-indireto.yaml) para o seu, na sua instalação de Home Assistante Core.

Esta configuração permitirá obter as seguintes entidades de consumo e estados, em valores instantâneos (à data de 05/07/2020):

* Tensão (V)
* Intensidade de corrente (A)
* Potência ativa (W)
* Frequência (Hz)
* Fator de potência (pu)
* Totalizador de energia consumida na tarifa 1 - Vazio
* Totalizador de energia consumida na tarifa 2 - Ponta
* Totalizador de energia consumida na tarifa 3 - Cheia
* Tarifa atual
* Estado do Disjuntor Controlador de Potência - DCP


## Aplicação das configurações

Deverá re-iniciar a sua instalação do Home Assistant Core e, posteriormente, poderá configurar um cartão do `lovelace`, conforme a seguinte proposta:

```yaml
entities:
  - entity: sensor.eb_tensao_l1
  - entity: sensor.eb_tensao_l2
  - entity: sensor.eb_tensao_l3
  - entity: sensor.eb_corrente_l1
  - entity: sensor.eb_corrente_l2
  - entity: sensor.eb_corrente_l3
  - entity: sensor.eb_potencia_activa
  - entity: sensor.eb_factor_de_potencia
  - entity: sensor.eb_frequencia
  - entity: sensor.eb_total_vazio_1
  - entity: sensor.eb_total_ponta_2
  - entity: sensor.eb_total_cheia_3
  - entity: sensor.eb_tarifa
  - entity: sensor.eb_estado_dcp
show_header_toggle: false
title: Contador
type: entities

```



# Mais info

[Voltar](../README.md)
