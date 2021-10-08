<hr>

Via syslog:

```sh
nc -u -l 514 > dump.txt
```

<hr>

Parsing:

```sh
cp dump.txt work.txt
sed -i -e 's/edp/\nedp/g' work.txt
cat work.txt | grep "ESP-:" | awk -F : '{ print $2 }' > work2.txt
sed -i -e 's/\n//g' work2.txt
sed -i -e 's/\r//g' work2.txt
tr -cd '\11\12\15\40-\176' < work2.txt > work3.txt
```

<hr>
