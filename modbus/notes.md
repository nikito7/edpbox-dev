version:

```js
vv=21.6.221
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"'${vv}'\",/g' manifest.json
```

debug:

```js
# configuration.yaml
logger:
  logs:
    homeassistant.components.modbus: debug
    pymodbus.client: debug
```
