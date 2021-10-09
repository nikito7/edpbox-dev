gui: raw

```yaml
alias: UPAC Update
description: 'UPAC Counters'
trigger:
  - platform: time_pattern
    hours: '*'
    minutes: '1'
  - platform: time_pattern
    hours: '*'
    minutes: '16'
  - platform: time_pattern
    hours: '*'
    minutes: '31'
  - platform: time_pattern
    hours: '*'
    minutes: '46'
condition: []
action:
  - service: input_number.set_value
    target:
      entity_id: input_number.upac_import
    data:
      value: >
        {% set counter = states('input_number.upac_import') %}
        {% set import = state_attr('sensor.utm_upac_pre_import', 'last_period')|float %}
        {% set export = state_attr('sensor.utm_upac_pre_export', 'last_period')|float %}
        {% set saldo = (import - export)|float %}
        {% if saldo > 0 %}
          {{ (counter|float + saldo)|float|round(2) }}
        {% else %}
          {{ counter|float }}
        {% endif %}
  - service: input_number.set_value
    target:
      entity_id: input_number.upac_export
    data:
      value: >
        {% set counter = states('input_number.upac_export') %} 
        {% set import = state_attr('sensor.utm_upac_pre_import', 'last_period')|float %}
        {% set export = state_attr('sensor.utm_upac_pre_export', 'last_period')|float %}
        {% set saldo = (import - export)|float %}
        {% if saldo < 0 %}
          {{ (counter|float + (saldo * -1))|float|round(2) }}
        {% else %}
          {{ counter|float }}
        {% endif %}
mode: single
```

yaml

```yaml
  utm_upac_pre_export:
    source: sensor.fake_export_kwh
    cycle: quarter-hourly

  utm_upac_pre_import:
    source: sensor.eb3_import
    cycle: quarter-hourly

  utm_upac_15min_export:
    source: input_number.upac_export
    cycle: quarter-hourly

  utm_upac_15min_import:
    source: input_number.upac_import
    cycle: quarter-hourly

###

  utm_upac_daily_export:
    source: input_number.upac_export
    cycle: daily

  utm_upac_daily_import:
    source: input_number.upac_import
    cycle: daily

  utm_upac_monthly_export:
    source: input_number.upac_export
    cycle: monthly

  utm_upac_monthly_import:
    source: input_number.upac_import
    cycle: monthly

```
