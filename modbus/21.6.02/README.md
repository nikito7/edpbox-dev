HA >= 2021.6

usage:

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

install:

```js
url=https://github.com/nikito7/edpbox/raw/dev/modbus/21.6.01/modbus-v21.6.01.zip
file=modbus-v21.6.01.zip
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
wget $url
unzip $file
rm $file
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"21.6.01\",/g' manifest.json
echo do: ha core restart
```

BETA
