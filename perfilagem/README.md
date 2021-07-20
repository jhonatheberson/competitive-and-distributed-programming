# Gprof

para usar o gprof parar analise do programa precisamos cimpilar o grograma com flag **-pg** desta forma:

```
/usr/bin/g++ -pg -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -c streamcluster.cpp


/usr/bin/g++ -pg -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -c parsec_barrier.cpp



/usr/bin/g++ -pg -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -L/usr/lib64 -L/usr/lib streamcluster.o parsec_barrier.o  -o streamcluster
```

e executar o programa normalmente, **./streamcluster 50 100 250 10000 1 10000 myin myout 2**

com a flag **-pg** irá gera um arquivo binario **gmon.out** para ler esse arquivo precisamos executar o gprof  da seguinte maneira:

```
gprof <executavel> gmon.out
```
assim ele vai gerar varias informações  importantes:
o **Flat profile:**, ele gera quanto tempo será executável para cada função


**Call graph (explanation follows)** quais a chamadas para isso,
e sequencia, também se utilizamos de **gprof2dot** para gerar um fluxograma do programa e suas chamadas

```
gprof <executavel> | gprof2dot | dot -Tpng -o output.png 
```

