custom component for home assistant 

usage:

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

dev notes:

```js
vv=21.6.02
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"${vv}\",/g' manifest.json
```
