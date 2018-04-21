#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <mpi.h>

#define MASTER 0

typedef struct {
    int x;
    int y;
    int r;
} dot;

void taking_cast(int l, int a, int b, int N, int rank, int size) {
    double t1, t2;

    if (rank == MASTER) {
        t1 = MPI_Wtime();
    }

    int seeds[size];
    int curr_seed;
    if (rank == MASTER) {
        srand(time(NULL));
        for (int i = 0; i < size; i++) {
            seeds[i] = (int) rand();
        }
    }
    MPI_Scatter(seeds, 1, MPI_INT, &curr_seed, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    dot *dots = (dot *) malloc(N * sizeof(dot));
    int dots_cap = N;
    srand(curr_seed);
    for (int i = 0; i < N; i++) {
        dots[i].x = rand() % l;
        dots[i].y = rand() % l;
        dots[i].r = rand() % (a * b);
    }

    int* cast = (int*) calloc(l * l * size, sizeof(int));

    for (int i = 0; i < N; i++) {
        int curr_x = dots[i].x;
        int curr_y = dots[i].y;
        int curr_r = dots[i].r;
        ++cast[l * curr_y * size + curr_x * size + curr_r];
    }

    MPI_File_delete("data.bin", MPI_INFO_NULL);

    MPI_File output;
    MPI_File_open(MPI_COMM_WORLD, "data.bin", MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &output);

    MPI_Datatype view;
    MPI_Type_vector(l, l * size, l * a * size, MPI_INT, &view);
    MPI_Type_commit(&view);

    int x = rank % a;
    int y = rank / a;
    int offset = (x * l + y * a * l * l) * size;

    MPI_File_set_view(output, offset * sizeof(int), MPI_INT, view, "native", MPI_INFO_NULL);

    MPI_File_write(output, cast, l * l * size, MPI_INT, MPI_STATUS_IGNORE);

    MPI_Type_free(&view);
    MPI_File_close(&output);

    if (rank == MASTER) {
        t2 = MPI_Wtime();

        FILE* stats = fopen("stats.txt", "w");
        fprintf(stats, "%d %d %d %d %lf", l, a, b, N, t2 - t1);
        fclose(stats);
    }

    free(cast);
    free(dots);
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int l = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    int N = atoi(argv[4]);

    taking_cast(l, a, b, N, rank, size);
    MPI_Finalize();
    return 0;
}
