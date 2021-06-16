From tasmota to esphome:
> - delete related yaml
> - ```ha core restart```
> - delete entities manually

From esphome to tasmota:
> - delete device first
> - add yaml stuff
> - ```ha core restart```

Without this you get duplicate ***_2 entities.
