custom component for home assistant 

usage:

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

```yaml
  count: 1
  data_type: string
  register_size: 12
```

install:

```js
url=
file=
mkdir -p /config/custom_components/modbus/
cd /config/custom_components/modbus/
wget $url
unzip $file
```
