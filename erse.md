```
url=https://github.com/dgomes/ha_erse/archive/refs/heads/master.zip
mkdir -p /config/custom_components/erse/
rm -rf /config/custom_components/erse/*
cd /config/custom_components/erse/
pwd && sleep 2
wget $url && unzip master.zip ha_erse-master/custom_components/erse/* -d .
rm master.zip
ls -a && ha core restart
```
