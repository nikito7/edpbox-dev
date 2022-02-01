Custom:

- adds "standard_size": yes/no.

Usage:

```yaml
      - name: "EB1 0x0001"
        slave: 1
        address: 1
        input_type: input
        count: 1
        data_type: custom
        standard_size: no
        structure: ">H7BhB"
        scan_interval: 7
```

Install:

```js
vv=2022.2-014
file=c-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/custom/${file}
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


