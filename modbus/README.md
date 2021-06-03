custom component for home assistant 

usage:

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

install:

HA <= 2021.5

```js
url=https://github.com/nikito7/edpbox/raw/dev/modbus/modbus-v21.4.zip
file=modbus-v21.4.zip
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
wget $url
unzip $file
rm $file
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"21.4\",/g' manifest.json
echo do: ha core restart
```
