#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data, i, myresult=0, result;
	int tag =123;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if (myid == 0) 
	{  
		 data=10;
	}
	for(i = 1;i < numprocs;i++)
	{
		if(myid == 0)
		{
			MPI_Send(&data,1,MPI_INT,i,tag, MPI_COMM_WORLD); 
		}
		else
		{
			MPI_Recv(&data,1,MPI_INT,0,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
	}
	printf("I got %d from %d\n", data, myid); 
	MPI_Finalize();
}
