Custom:

- adds "register_size"

Usage:

```yaml
  count: 1
  data_type: custom
  register_size: 4
  structure: ">L"
```

Install:

```js
vv=21.8.081
file=custom-${vv}.zip
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


