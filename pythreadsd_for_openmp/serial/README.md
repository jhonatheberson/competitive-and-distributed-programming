# Compile

```
/usr/bin/g++ -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -c streamcluster_serial.cpp
```

```
/usr/bin/g++ -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -L/usr/lib64 -L/usr/lib streamcluster_serial.o  -o streamcluster_serial
```

# Run

```
time ./streamcluster_serial 10 20 200 1000 1 1000 myin myout 1

>> ./streamcluster_serial 10 20 200 1000 1 1000 myin myout 1  0,93s user 0,00s system 99% cpu 0,935 total
```