# Vetorização

iremos fazer que o compilador mostre qual parte do codigo não foi realizado a vetorização e porque para tentar melhora-lo a vetorização, é uma técnica que o compilador tenta executar um loop em apenas um ciclo de clock, usando a arquitetura do processador vetorizado.

para isso utilizamos a seguintes **flags** no compilador:

- ```-O3 -fopt-info-vec-all -> todas as informações```
- ```-O3 -fopt-info-vec-missed -> só os não otimizados  ```
- ```-O3 -fopt-info-vec-optimized  -> só os otimizados  ```


em nosso programa utilizei da seguinte forma:

```
/usr/bin/g++ -pg -O3 -fopt-info-vec-missed -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -c streamcluster.cpp  2>&1 | tee fopt-info-vec-missed_streamclsuter.txt
```


com a seguinte saida:

[fopt-info-vec-missed_streamclsuter](fopt-info-vec-missed_streamclsuter.txt)


```
/usr/bin/g++ -pg -O3 -fopt-info-vec-missed -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -c parsec_barrier.cpp  2>&1 | tee fopt-info-vec-missed_parsec_barrier.txt
```

[fopt-info-vec-missed_parsec_barrier](fopt-info-vec-missed_parsec_barrier.txt)


