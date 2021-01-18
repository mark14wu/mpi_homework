#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#define P 2

int main(int argc, char* argv[]) {
	MPI_Comm MyWorld, SplitWorld;
	int rank, size, group_rank, group_size, color, key, tag = 1;
	int i;
	double old_data, new_data;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &MyWorld);
	MPI_Comm_rank(MyWorld, &rank);
	MPI_Comm_size(MyWorld, &size);
	color = rank % P;
	key = rank / P;
	MPI_Comm_split(MyWorld, color, key, &SplitWorld);
	MPI_Comm_rank(SplitWorld, &group_rank);
	MPI_Comm_size(SplitWorld, &group_size);
	srand(rank + (unsigned)time(NULL));
	while (1) {
		if (group_rank != 0) {
			old_data = rand() % 100;
			printf("Before : rank =  %2d, data =  %f\n", rank, old_data);
			MPI_Send(&old_data, 1, MPI_DOUBLE, 0, tag, SplitWorld);
			MPI_Recv(&new_data, 1, MPI_DOUBLE, 0, tag, SplitWorld, &status);
			printf("After  : rank =  %2d, data =  %f\n", rank, new_data);
		}
		new_data = 0;
		for (i = 1; i < group_size; i++) {
			MPI_Recv(&old_data, 1, MPI_DOUBLE, i, tag, SplitWorld, &status);
			new_data += old_data;
		}
		if (i / P == 0 && i != rank) {
			MPI_Send(&new_data, 1, MPI_DOUBLE, i, tag, MyWorld);
			MPI_Recv(&old_data, 1, MPI_DOUBLE, i, tag, MyWorld, &status);
			new_data += old_data;
		}
	}
	new_data /= (size - P);
	MPI_Send(&new_data, 1, MPI_DOUBLE, i, tag, SplitWorld);
}
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}