#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x,k, low, high, myresult=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int rec_size=MAXSIZE;
	int result[rec_size],j,n;
	if (myid == 0) 
	{  
		for(i = 0; i < MAXSIZE; i++)
			data[i]=i+1;
	}
	x = MAXSIZE/numprocs; 
	int recv_data[x];
	int gather_data[x];
	MPI_Scatter(data,x,MPI_INT,recv_data,x, MPI_INT,0,MPI_COMM_WORLD);
	if(myid==0)
	{	
		for(k=0;k<x;k++)
		{
			result[k]=recv_data[k];
		}
		for(i=1;i<numprocs;i++)
		{
			MPI_Recv(gather_data,x,MPI_INT,i,123,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			for(j=0;j<x;j++)
			{
				result[k]=gather_data[j];
				k++;
			}
		}
	}
	else
	{
		MPI_Send(recv_data,x,MPI_INT,0,123,MPI_COMM_WORLD);
	}
	if (myid == 0) 
	{
		for(i=0;i<MAXSIZE;i++)
		{
			printf("The array %d.\n", result[i]);
		}
	}
	MPI_Finalize();
}
