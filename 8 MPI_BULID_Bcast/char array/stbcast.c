#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 14
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, low, high, result;
	int tag =123;
	char messag[MAXSIZE]="hello MPI User";
	char myresult[MAXSIZE];
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if (myid == 0) 
	{  
		for(i = 0; i < MAXSIZE; i++)
			data[i]=i;
	}
	for(i = 1;i < numprocs;i++)
	{
		if(myid == 0)
		{
			MPI_Send(messag,MAXSIZE,MPI_CHAR,i,tag, MPI_COMM_WORLD); 
		}
		else
		{
			MPI_Recv(messag,MAXSIZE,MPI_CHAR,0,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
	}
	printf("I got %s from %d\n", messag, myid); 
	MPI_Finalize();
}
