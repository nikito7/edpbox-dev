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

# Install

```js
vv=21.7.052
file=modbus-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/${file}
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
ls -la
pwd
sleep 5
cd /config/custom_components/modbus/
wget $url
unzip $file
rm $file
ls -la
pwd
sleep 1
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"'${vv}'\",/g' manifest.json
sleep 3
ha core restart
```
