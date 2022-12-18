#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, low, high, myresult=0 ,temp_result,last_result=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if (myid == 0) 
	{  
		for(i = 0; i < MAXSIZE; i++)
			data[i]=i;
	}
	int result[numprocs];
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	x = MAXSIZE/numprocs; 
	low = myid * x;
	high = low + x;
	for(i = low; i < high; i++)
		myresult += data[i];
	printf("I got %d from %d\n", myresult, myid); 
	if(myid==0)
	{	
		last_result+=myresult;
		for(i = 1; i < numprocs; i++)
		{
			temp_result=0;
			MPI_Recv(&temp_result,1,MPI_INT,i,123,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			last_result+=temp_result;
		}
	}
	else if(myid!=0)
	{	
		MPI_Send(&myresult,1,MPI_INT,0,123,MPI_COMM_WORLD);
	}
	if (myid == 0) printf("The sum is %d.\n", last_result);
	MPI_Finalize();
}
