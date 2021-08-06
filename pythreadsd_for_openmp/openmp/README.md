# Compile

```
/usr/bin/g++ -fopenmp -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -c streamcluster_openmpi.cpp  
```

```
/usr/bin/g++ -fopenmp -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -L/usr/lib64 -L/usr/lib streamcluster_openmpi.o  -o streamcluster_openmpi
```

# Run

```
time ./streamcluster_openmpi 10 20 200 1000 1 1000 myin myout 2
```