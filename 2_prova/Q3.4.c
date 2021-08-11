/* File:     mpi_output.c
 *
 * Purpose:  A program in which multiple MPI processes try to print 
 *           a message.
 *
 * Compile:  mpicc -g -Wall -o mpi_output mpi_output.c
 * Usage:    mpiexec -n<number of processes> ./mpi_output
 *
 * Input:    None
 * Output:   A message from each process
 *
 * IPP:      Section 3.3.1  (pp. 97 and ff.)
 */
#include <stdio.h>
#include <mpi.h> 

int main(void) {
   int my_rank, comm_sz, send = 0;

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if(my_rank ==0) {
    printf("Proc %d of %d > Does anyone have a toothpick?\n",
         my_rank, comm_sz);
    // int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest,
    //int tag, MPI_Comm comm)
    MPI_Send(&send,1,MPI_INT,my_rank+1,0,MPI_COMM_WORLD);
   }
   // recebe do rank anterior e se não for o ultimo envia para proximo 
   else{
      //receb do processo (rank) anterior
      //int MPI_Recv(void *buf, int count, MPI_Datatype datatype,
      //int source, int tag, MPI_Comm comm, MPI_Status *status)
      MPI_Recv(&send,1,MPI_INT, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Proc %d of %d > Does anyone have a toothpick?\n",
         my_rank, comm_sz);
      // envia para o proximo se não for ultimo processo
      if (my_rank < comm_sz-1){
        MPI_Send(&send,1,MPI_INT, my_rank+1, 0, MPI_COMM_WORLD);
      }

   }


   MPI_Finalize();
   return 0;
}  /* main */
