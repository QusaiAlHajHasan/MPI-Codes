#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i,y, x, low, high, myresult=0, result;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	for(y = 0; y < numprocs; y++)
	{
		if (myid == y) 
		{  
			for(i = 0; i < MAXSIZE; i++)
			{
			
				 data[i]=i+1;
			
			}
		}
	}
	//x = MAXSIZE/numprocs; 
	//int recv_data[x];

	
	//MPI_Scatter(data,x,MPI_INT,recv_data,x, MPI_INT,0,MPI_COMM_WORLD);
	for(i = 0; i < MAXSIZE; i++)
		if(myresult > recv_data[i])
			myresult=recv_data[i];
	printf("I got %d from %d\n", myresult, myid); 
	MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	if (myid == 0) printf("The MIN is %d.\n", result);
	MPI_Finalize();
}
