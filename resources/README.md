## Make commands

```sh
make            # Compile all dependencies and libraries
make clean      # Cleanup files (except submodules and generated client files)
```

## Running

```
./generator NUM_CLIENTS START_TIME END_TIME [-t]

NUM_CLIENTS         Number of clients
START_TIME          Time clients start arriving (in hours)
END_TIME            Time clients end arriving (in hours)
-t                  Consider clients only want to be transported from the station to elsewhere
```

### Examples
```sh
./generator   8 8  8.25 -t > it1_01.clients
./generator  30 8 22    -t > it1_02.clients
./generator 100 8 22    -t > it1_03.clients
```