Info:

https://github.com/tiagofreire-pt/Home_Assistant_EDP_Box/ 🇵🇹

https://tasmota.github.io/docs/Smart-Meter-Interface/ 🇬🇧

Convert EB1 to EB2 yaml:

```js
sed -i -e 's/EB1/EB2/g' tasmota-eb2mono.yaml
sed -i -e 's/edpbox1/edpbox2/g' tasmota-eb2mono.yaml
```

