# dev: default

- no mod

```js
vv=21.7.121
file=dev-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/dev/${file}
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

# dev: custom

- register_size

```js
vv=21.7.131
file=custom-${vv}.zip
url=https://github.com/nikito7/edpbox/raw/dev/modbus/dev/${file}
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
