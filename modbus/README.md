# Info

- Custom component for HA!
- Add register_size for modbus
- Allow non-standard registers size

# Usage

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

```yaml
  count: 1
  data_type: string
  register_size: 10
```

# Install 21.6.261

```js
vv=21.6.261
file=modbus-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/${file}
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
ls -a
pwd
wget $url
unzip $file
rm $file
ls -a
pwd
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"'${vv}'\",/g' manifest.json
ha core restart
```

# Install 21.6.221

```js
vv=21.6.221
file=modbus-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/${file}
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
ls -a
pwd
wget $url
unzip $file
rm $file
ls -a
pwd
#sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"'${vv}'\",/g' manifest.json
ha core restart
```
