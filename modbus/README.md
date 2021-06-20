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

# 21.6.201

- removed register_size from string
- updated base code

```js
vv=21.6.201
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
# ha core restart
```
