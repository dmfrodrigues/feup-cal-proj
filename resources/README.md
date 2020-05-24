## Make commands

```sh
make            # Compile all dependencies and libraries
make clean      # Cleanup files (except submodules and generated client files)
```

## Running

```
./generator OUTPUT_FILE NUM_CLIENTS TIME_START TIME_END [-t]

OUTPUT_FILE         Name of output file
NUM_CLIENTS         Number of clients
START_TIME          Time clients start arriving (in hours)
END_TIME            Time clients end arriving (in hours)
-t                  Consider clients only want to be transported from the station to elsewhere
```

### Examples
```sh
./generator it1_01.clients  8   8   8.25    -t
./generator it1_02.clients  30  8   22      -t
./generator it1_03.clients  100 8   22      -t
```