
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	long thread_count;
	int i, iteracoes;

	thread_count = strtol(argv[1], NULL, 10);

	printf("Insira a quantidade de iteraÃ§Ãµes: ");
	scanf("%d", &iteracoes);
	printf("\n");

	# pragma omp parallel num_threads(thread_count)

		# pragma omp for

			for (i = 0; i < iteracoes; ++i) {
				printf("Thread %d - IteraÃ§Ã£o %d\n", omp_get_thread_num(), i);
			}

	return 0;
}