Info:

https://tasmota.github.io/docs/Smart-Meter-Interface/ 

Disable recovery mode:

> If you have a weak power grid or 
> frequent power brownouts its best to disable
> this feature with 
> SetOption65 1 
> immediately 
> or you'll end up with firmware default
> devices after a brownout event.

Timezone:

```
Backlog TimeZone 99; TimeDST 0,0,3,1,1,60; TimeSTD 0,0,10,1,2,0
```
Erro 84/81:

![erro 84 81](./erro81.jpg)

Rename:

```
sed -i -e 's/edpbox3/edpbox5/g' tasmota5.yaml
sed -i -e 's/EB3/EB5/g' tasmota5.yaml
sed -i -e 's/eb3/eb5/g' tasmota5.yaml
```

[![Discord](https://img.shields.io/discord/494714310518505472?style=plastic&logo=discord)](https://discord.gg/Mh9mTEA) 
