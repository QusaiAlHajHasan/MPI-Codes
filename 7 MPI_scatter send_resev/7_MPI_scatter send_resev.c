#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 12
void main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, maxf, minf, sumf=0, prodf=1;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Status* status;
	
	if (myid == 0) 
	{  
		for(i = 0; i < MAXSIZE; i++) data[i]=i+1;
	}

	x = MAXSIZE/numprocs; 
	int recv_data[x];
	MPI_Scatter(data,x,MPI_INT,recv_data,x,MPI_INT,0,MPI_COMM_WORLD);

	if(myid==0)//prod
	{
		for(i = 0; i < x; i++)
			prodf *= recv_data[i];
		MPI_Recv(&maxf,1,MPI_INT,1,123,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&minf,1,MPI_INT,2,124,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&sumf,1,MPI_INT,3,125,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("the sum = %d\n", sumf); 
		printf("the min = %d\n", minf); 
		printf("the max = %d\n", maxf); 
		printf("the prod = %d\n", prodf);
	}
	else if(myid==1)//max
	{	
		int max=0;
		for(i = 0; i < x; i++)
			if(max < recv_data[i])
				max=recv_data[i];
		MPI_Send(&max,1,MPI_INT,0,123,MPI_COMM_WORLD);
	}
	else if(myid==2)//min
	{
		int min=10000;
		for(i = 0; i < x; i++)
			if(min > recv_data[i])
				min=recv_data[i];
		MPI_Send(&min,1,MPI_INT,0,124,MPI_COMM_WORLD);
	}
	else if(myid==3)//sum
	{
		int sum=0;
		for(i = 0; i < x; i++)
			sum+=recv_data[i];
		MPI_Send(&sum,1,MPI_INT,0,125,MPI_COMM_WORLD);
	}
	
	
	MPI_Finalize();
}
