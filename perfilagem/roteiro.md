ngelo Leite Medeiros Goes
Angelo Marcelino Cordeiro
Jhonat Heberson Avelino de Souza
Mauricio Thiago Ferreira de Lima

# Roteiro da apresentação

## k-means

quantidades de centros iniciais, influencia diretamente na qualidade do resultado **(hiperparametro)**

Este processo é iterativo, e os centros são recalculados aleatoriamente 
até que a variância das distâncias centro-pontos 
não tenha grande alteração. O parâmetro de similaridade 
entre os dados e os centros normamente é definida atráves da distância euclidiana.

Após atribuir todos os dados a um centro, estes são atualizado com
o valor médio dos dados atribuídos.

- Até atingir um pré-determinado número de iterações.
- Quando os centros estabilizarem (não houver mais alteração no
valor).

## Implementação

Argumentos passíveis de customização são: K mínimo (k1) , K máximo (k2), número de dimensões (d), 
número de data points (n), número de data points processados por iteração (chunksize), 
número máximo de pontos intermediários (chunksize), arquivo de entrada (infile), arquivo de saída (outfile), 
e número de threads (nproc).

O comando de execução tem formato: 
./streamcluster k1 k2 d n chunksize clustersize infile outfile nproc

Após verificar que o código estava funcionando, o perfilamento foi realizado com o uso da ferramenta Gprof. 
O projeto foi então compilado, utilizando a variável de ambiente, através de 3 comandos com a flag “-pg”: 

/usr/bin/g++ -pg -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive 
-fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed 
-DPARSEC_VERSION=3.0-beta-20150206 -DENABLE_THREADS -pthread -c streamcluster.cpp

/usr/bin/g++ -pg -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive 
-fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206
 -DENABLE_THREADS -pthread -c parsec_barrier.cpp

/usr/bin/g++ -pg -O3 -g -funroll-loops -fprefetch-loop-arrays -fpermissive
 -fno-exceptions -static-libgcc -Wl,--hash-style=both,--as-needed -DPARSEC_VERSION=3.0-beta-20150206 
 -DENABLE_THREADS -pthread -L/usr/lib64 -L/usr/lib streamcluster.o parsec_barrier.o  -o streamcluster

## Perfilagem

Inicialmente foram compilados os arquivos streamcluster.o e parsec_barrier.o,
 e por fim o streamcluster.  A flag “-pg”  foi usada para gerar o arquivo gmon.out, 
 arquivo de análise Gprof.

Após análise do perfilamento foi observado que a maior parte das chamadas e tempo de processamento 
estão distribuídas entre 5 funções específicas, 2 delas tomando mais de 90% do 
tempo de execução para todas as configurações aferidas: “pgain” e “parsec_barrier_wait”.

“pgain” é a função mais algoritmicamente exaustiva, já que nela é calculada
 o ganho na variância entre centros, para todos os pontos. Possui 2 “for” aninhados
  portanto sua complexidade é de O(n^2). Esta e suas auxiliares são as que mais geram gargalo.

“parsec_barrier_wait” por sua vez implementa barreiras e para sincronização de threads. 
Gera latência pois as threads ficam ociosas enquanto esperam umas às outras. 
Muito tempo foi perdido mesmo quando nproc = 1, ou seja, com uma thread, 
o que teoricamente não deveria acontecer já que não há o que sincronizar quando se tem apenas um processo. 
Por fim, a maior parte de suas chamadas vem de “pgain”.

Se observou que com mais threads havia mais espera, logo mais atraso, 
que não deveria ser o caso já que o uso de mais processos deveria diminuir a latência. 
E mesmo com nproc = 1 (uma thread em execução) muito tempo foi perdido na função.

## Conclusão

uso de **chunksize** (hiperparametro) diminuto, isso leva o núcleo a demorar muito somente na leitura dos pontos. 
Quando lê em pedaços maiores, reduz-se a latência. 

Também, funções como “pgain” parecem gastar bastante tempo (aprox. 80%+), 
especialmente por ter maior parte dos loops no programa, 
ser a função mais algebricamente dispendiosa e ter complexidade O(n^2). “pgain” 
também chama diversas funções auxiliares, como “parsec_barrier_wait”,
a segunda mais dispendiosa, responsável por sincronizar threads. 

Para sincronização de threads são utilizadas pthread barriers, ou barreiras de threads,
ao longo de toda execução do código.
percemos que mais threads havia mais espera e
muito tempo foi perdido na função, comportamento julgado anômalo, 
já que não há o que sincronizar tendo um único processo. 
Tudo isso indicaria que há erro na implementação das barreiras.



