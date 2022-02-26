https://github.com/home-assistant/core/archive/refs/heads/master.zip

```sh
file=master.zip
url=https://github.com/home-assistant/core/archive/refs/heads/${file}
#
mkdir -p /config/custom_components/modbus/
rm -rf /config/custom_components/modbus/*
cd /config/custom_components/modbus/
ls -a
pwd
#
wget $url
unzip $file
rm $file
ls -a
pwd
# version
sed -i -e 's/\"name\": \"Modbus\",/\"name\": \"Modbus\",\n  \"version\": \"'${vv}'\",/g' manifest.json
# tweak
#ha core restart
```
