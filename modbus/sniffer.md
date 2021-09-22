> minicom log

> new lines

```sh
sed -i -e 's/01 04 /\n:: 01 04 /g' ttyUSB0.log
```

> "inverso"

```sh
sed -i -e 's/7f 9f /\n:: 7f 9f /g' ttyUSB0.log
```
