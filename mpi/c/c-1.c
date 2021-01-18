#include <stdio.h>
#include <mpi.h>

void butterfly_sum(int rank, int size) {
    int sum = rank, step = 2, dst, temp;
    while(step <= size) {
        if(rank%step < step/2)
            dst = rank + step/2;
        else
            dst = rank - step/2;

        MPI_Sendrecv(&sum, 1, MPI_INT, dst, 0,
                    &temp, 1, MPI_INT, dst, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum += temp;
        step *= 2;
    }
    if(rank == 0)
        printf("%d\n", sum);
}

void btree_sum(int rank, int size) {
	int remain = size, sum = rank, half, temp;
	while (remain != 1) {
		half = remain / 2;
		if (rank < half) {
			MPI_Recv(&temp, 1, MPI_INT, rank + half, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += temp;
		}
		else {
			MPI_Send(&sum, 1, MPI_INT, rank - half, 0, MPI_COMM_WORLD);
			return;
		}
		remain = half;
	}
	if (rank == 0)
		printf("%d\n", sum);
}

int main() {
    int size;
    int rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    butterfly_sum(rank, size);
	//btree_sum(rank, size);
    MPI_Finalize();
    return 0;
}