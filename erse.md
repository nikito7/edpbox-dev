```
mkdir -p /config/custom_components/erse/
rm -rf /config/custom_components/erse/*
cd /config/custom_components/erse/
pwd
sleep 2
wget https://github.com/dgomes/ha_erse/archive/refs/heads/master.zip
unzip master.zip
mv ha_erse-master/custom_components/erse/* .
rm master.zip
rm -rf ha_erse-master
```
