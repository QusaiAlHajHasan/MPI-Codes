#include <stdio.h>
#include <mpi.h>
#include <math.h>
#define MAXSIZE 4
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE][MAXSIZE], i,y,j, x, low, high, myresult=0, result;
	int vector[MAXSIZE];
	int output[MAXSIZE];
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	for(i = 0; i < MAXSIZE; i++)
	{
		vector[i]=2;
		for(j = 0; j < MAXSIZE; j++)
		{
		 	data[i][j]=2;
		}
	}
	MPI_Bcast(vector,MAXSIZE,MPI_INT,0,MPI_COMM_WORLD); 
	x = MAXSIZE/numprocs; 
	int recv_data[x][MAXSIZE];
	MPI_Scatter(data,MAXSIZE*x,MPI_INT,recv_data,MAXSIZE*x,MPI_INT,0,MPI_COMM_WORLD);
	int sum[x];
	for(j = 0; j < x; j++)
	{
		sum[j]=0;
	}
	for(j = 0; j < x; j++)
	{
		for(i = 0; i < MAXSIZE; i++)
		{
		    	sum[j]+=recv_data[j][i]*vector[i];
		}
	}
	MPI_Gather(sum,x,MPI_INT,output,x,MPI_INT,0,MPI_COMM_WORLD);
	if(myid==0)
	{
		for(i = 0; i < MAXSIZE; i++)
		{
			printf("output vector %d\n", output[i]); 
		}
	}
	MPI_Finalize();
}
