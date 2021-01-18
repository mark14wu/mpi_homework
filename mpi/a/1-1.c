#include <mpi.h>
#include <stdio.h>
 
void main(int argc,char *argv[])
{
	MPI_Comm MyWorld, SplitWorld;
	int my_rank,group_size, Color, Key;
	char message[80] = "this is no.x node";
	
	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD,&MyWorld);
	MPI_Comm_rank(MyWorld,&my_rank);
	MPI_Comm_size(MyWorld,&group_size);
	
	Color=my_rank%3;
	Key=my_rank/3;
 
	if(my_rank/3 == 0)
		message[11] = my_rank + '0';
	
	MPI_Comm_split(MyWorld,Color,Key,&SplitWorld);
 
	MPI_Bcast(message,80,MPI_CHAR,0,SplitWorld);
 
	printf("node: %d message: %s\n",my_rank,message);
 
	MPI_Finalize();
}

