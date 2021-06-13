# Usage

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

# Install

```js
vv=v21.6.03
file=modbus-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/${vv}/${file}
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
pwd
ls -la
```

```js
cd /config/custom_components/modbus/
wget $url
unzip $file
rm $file
```

ha core restart
