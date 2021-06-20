Custom component for home assistant!

Usage:

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

21.6.03 Install:

```js
vv=21.6.03
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
# ha core restart
```

21.6.201 Install:

- removed register_size from string
- updated base

```js
vv=21.6.201
file=modbus-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/${file}
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
pwd
ls -la
sleep 5
cd /config/custom_components/modbus/
wget $url
unzip $file
rm $file
pwd
ls -la
# ha core restart
```

EOF
