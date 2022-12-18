#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int dataA[MAXSIZE], i, x, maxf, minf, sumf=0, prodf=1;
	int dataB[MAXSIZE];
	int dataC[MAXSIZE];
	int tag =123;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Status* status;
	if (myid == 0) 
	{  
		for(i = 0; i < MAXSIZE; i++)
		{
			dataA[i]=i;
			dataB[i]=i;
		}
	}
	x = MAXSIZE/numprocs; 
	int recv_dataA[x];
	int recv_dataB[x];
	int recv_dataC[x];
	MPI_Scatter(dataA,x,MPI_INT,recv_dataA,x,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(dataB,x,MPI_INT,recv_dataB,x,MPI_INT,0,MPI_COMM_WORLD);
	for(i = 0;i < x;i++)
	{
		recv_dataC[i]=recv_dataA[i]*recv_dataB[i];
	}
	MPI_Gather(recv_dataC,x,MPI_INT,dataC,x,MPI_INT,0,MPI_COMM_WORLD);
	if (myid == 0) 
	{
		for(i=0;i<MAXSIZE;i++)
		{
			printf("The array %d.\n", dataC[i]);
		}
	}
	MPI_Finalize();
}
