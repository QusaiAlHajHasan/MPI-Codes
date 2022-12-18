#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, low, high, myresult=100, result;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if (myid == 0) {  
		
	for(i = 0; i < MAXSIZE; i++) data[i]=i+1;
	}
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	x = MAXSIZE/numprocs; 
	low = myid * x;
	high = low + x;
	for(i = low; i < high; i++)
		if(myresult > data[i])
			myresult=data[i];
	printf("I got %d from %d\n", myresult, myid); 
	MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	if (myid == 0) printf("The MIN is %d.\n", result);
	MPI_Finalize();
}
