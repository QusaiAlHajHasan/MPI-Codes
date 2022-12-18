#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, low, high, myresult=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int rec_size=MAXSIZE*numprocs;
	int result[rec_size];
	if (myid == 0)
	{  	
	for(i = 0; i < MAXSIZE; i++)
		data[i] = i;
	}
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	x = MAXSIZE/numprocs; 
	low = myid * x;
	high = low + x;
	printf("I got %d from %d\n", myresult, myid); 
	MPI_Gather(&data,MAXSIZE,MPI_INT,&result,MAXSIZE,MPI_INT,0,MPI_COMM_WORLD);
	if (myid == 0) 
	{
		for(i=0;i<rec_size;i++)
		{
			printf("The array %d.\n", result[i]);
		}
	}
	MPI_Finalize();
}
