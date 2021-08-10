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

>> ./streamcluster_openmpi 10 20 200 1000 1 1000 myin myout 2  0,53s user 0,01s system 173% cpu 0,311 total
```

# Results

## function pgain

- First for


  ~~~c++
  #pragma omp parallel num_threads(nproc)
      #pragma omp for
        for( int i = 0; i < points->num; i++ ) {
          if(is_center[i]) {
            center_table[i] = count++;
          }
        }
  ~~~

    conseguimos o seguinte tempo de execução

    ~~~bash
      ./streamcluster_openmpi 10 20 200 1000 1 1000 myin myout 2  0,69s user 0,03s system 184% cpu 0,386 total
    ~~~

- Second For


  ~~~c++
  #pragma omp parallel num_threads(nproc)
      #pragma omp for
        for ( i = 0; i < points->num; i++ ) {
          x_cost_arr[i] =  dist(points->p[i], points->p[x], points->dim);
          x_cost_arr[i] *= points->p[i].weight;
        }
  ~~~

  conseguimos o seguinte tempo de execução

  ~~~bash
  /streamcluster_openmpi 10 20 200 1000 1 1000 myin myout 2  0,80s user 0,00s system 184% cpu 0,433 total
  ~~~


 - Tree For


 ~~~c++
#pragma omp parallel num_threads(nproc)
    #pragma omp for
      for ( i = 0; i < points->num; i++ ) {
        float current_cost = points->p[i].cost;

        if ( x_cost_arr[i] < current_cost ) {
          switch_membership[i] = 1;
          cost_of_opening_x += x_cost_arr[i] - current_cost;

        } else {
          int assign = points->p[i].assign;
          lower[center_table[assign]] += current_cost - x_cost_arr[i];
        }
      }
 ~~~
conseguimos o seguinte speedup:

 ~~~bash
./streamcluster_openmpi 10 20 200 1000 1 1000 myin myout 2  0,48s user 0,00s system 175% cpu 0,279 total
 ~~~

 novamento vamos paralelizar outro for que é esse:


 ~~~c++
#pragma omp parallel num_threads(nproc)
    #pragma omp for
      for ( i = 0; i < points->num; i++ ) {
        float current_cost = points->p[i].cost;

        if ( x_cost_arr[i] < current_cost ) {
          switch_membership[i] = 1;
          cost_of_opening_x += x_cost_arr[i] - current_cost;

        } else {
          int assign = points->p[i].assign;
          lower[center_table[assign]] += current_cost - x_cost_arr[i];
        }
      }
 ~~~
conseguimos o seguinte speedup:

  ~~~bash
  ./streamcluster_openmpi 10 20 200 1000 1 1000 myin myout 2  0,48s user 0,00s system 175% cpu 0,279 total
  ~~~