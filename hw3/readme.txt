# CSE4116 HW3 stopwatch with interrupt handler

### device number
- major# : 242
- minor# : 0

### build

#### for module
```
cd module
make
```

#### for app
```
cd app
make
```

### deploy

#### for module
```
// in host
sh module/scripts/deploy.sh

// in target
sh module/scripts/regist_mod.sh
```

#### for app
```
// in host
sh app/deploy.sh
```

### run
```
// in target
// pwd: ~/data/local/tmp
./app
```

