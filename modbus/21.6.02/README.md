# Usage

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

# Install

```js
file=modbus-v21.6.02.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/21.6.02/${file}
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
```

```js
cd /config/custom_components/modbus/
wget $url
unzip $file
rm $file
```

```js
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"21.6.02\",/g' manifest.json
```

ha core restart
