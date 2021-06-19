Test: 4 bytes only

# Usage

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

# Install

```js
vv=21.6.test1
file=modbus-v${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/${vv}/${file}
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
pwd
ls -la
sleep 3
cd /config/custom_components/modbus/
wget $url
unzip $file
rm $file
pwd
ls -la
```

version:

```js
vv=21.6.test1
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"'${vv}'\",/g' manifest.json
```

ha core restart
