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
	int res_size=2*MAXSIZE;
	int result[res_size];
	if (myid == 0)
	{  
	for(i = 0; i < MAXSIZE; i++)
		data[i]=i;
	}
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	for(i=0;i<numprocs;i++)
	{
		MPI_Gather(data,MAXSIZE,MPI_INT,result,MAXSIZE,MPI_INT,i,MPI_COMM_WORLD);
	}
	for(i=0;i<res_size;i++)
	{
		myresult+=result[i];
		printf("the sum after all gather : %d from %d\n", myresult, myid);
	}
	MPI_Finalize();
}
