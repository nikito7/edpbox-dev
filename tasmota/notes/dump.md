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
```

<hr>
