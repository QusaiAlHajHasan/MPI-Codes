#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, low, high, myresult=0, result;
	int tag =123;
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
			MPI_Send(data,MAXSIZE,MPI_INT,i,tag, MPI_COMM_WORLD); 
		}
		else
		{
			MPI_Recv(data,MAXSIZE,MPI_INT,0,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
	}
	x = MAXSIZE/numprocs; 
	low = myid * x;
	high = low + x;
	for(i = low; i < high; i++)
		myresult += data[i];
	printf("I got %d from %d\n", myresult, myid); 
	MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0) printf("The sum is %d.\n", result);
	MPI_Finalize();
}
