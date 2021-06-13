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
sed -i '.bak' -e \
's/\"name\": \"Modbus\"\
,/\"name\": \"Modbus\",\
\n  \"version\": \"21.6.02\",/g' \
manifest.json
```
