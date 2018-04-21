#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <mpi.h>

#define MASTER 0
#define GROWTH_FACTOR 2

typedef struct {
    int x;
    int y;
    int steps_left;
    int rank;
} dot;

void random_walk(int l, int a, int b, int n, int N, double p_l, double p_r, double p_u, double p_d, int rank, int size) {
    int seeds[size];
    int curr_seed;
    if (rank == MASTER) {
        srand(time(NULL));
        for (int i = 0; i < size; i++) {
            seeds[i] = (int) rand();
        }
    }
    MPI_Scatter(seeds, 1, MPI_INT, &curr_seed, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    dot* dots = (dot*) malloc(N * sizeof(dot));
    int dots_cap = N;
    srand(curr_seed);
    for (int i = 0; i < N; i++) {
        dots[i].x = rand() % l;
        dots[i].y = rand() % l;
        dots[i].steps_left = n;
        dots[i].rank = rank;
    }

    int l_sq_rank, r_sq_rank, u_sq_rank, d_sq_rank;
    int x = rank % a;
    int y = rank / a;
    if (x < 1) {
        l_sq_rank = y * a + a - 1;
    } else {
        l_sq_rank = y * a + x - 1;
    }
    if (x >= a - 1) {
        r_sq_rank = y * a;
    } else {
        r_sq_rank = y * a + x + 1;
    }
    if (y < 1) {
        u_sq_rank = (b - 1) * a + x;
    } else {
        u_sq_rank = (y - 1) * a + x;
    }
    if (y >= b - 1) {
        d_sq_rank = x;
    } else {
        d_sq_rank = (y + 1) * a + x;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    dot* to_left_sq = (dot*) malloc(sizeof(dot) * N);
    dot* to_right_sq = (dot*) malloc(sizeof(dot) * N);
    dot* to_up_sq = (dot*) malloc(sizeof(dot) * N);
    dot* to_down_sq = (dot*) malloc(sizeof(dot) * N);
    int cap_left = N, pos_left = 0;
    int cap_right = N, pos_right = 0;
    int cap_up = N, pos_up = 0;
    int cap_down = N, pos_down = 0;


    dot* finished_dots = (dot*) malloc(sizeof(dot) * N);
    int cap_fin = N, pos_fin = 0;
    int dots_pos = N;

    double t1, t2;
    if (rank == MASTER) {
        t1 = MPI_Wtime();
    }
    while (1) {
        int curr_ind = 0;
        while (curr_ind < dots_pos) {
            dot curr_dot = dots[curr_ind];

            for (int j = 0; j < 500; j++) {
                if (curr_dot.steps_left != 0) {
                    curr_dot.steps_left -= 1;

                    double l_step = rand() * p_l;
                    double r_step = rand() * p_r;
                    double u_step = rand() * p_u;
                    double d_step = rand() * p_d;
                    if (l_step >= r_step && l_step >= u_step && l_step >= d_step) {
                        curr_dot.x -= 1;
                    } else if (r_step >= l_step && r_step >= u_step && r_step >= d_step) {
                        curr_dot.x += 1;
                    } else if (u_step >= l_step && u_step >= r_step && u_step >= d_step) {
                        curr_dot.y += 1;
                    } else {
                        curr_dot.y -= 1;
                    }

                    if (curr_dot.x < 0) {
                        curr_dot.x = l - 1;
                        if (pos_left == cap_left) {
                            to_left_sq = (dot*) realloc(to_left_sq, sizeof(dot) * cap_left * GROWTH_FACTOR);
                            cap_left *= GROWTH_FACTOR;
                        }
                        to_left_sq[pos_left] = curr_dot;
                        pos_left++;

                        dots[curr_ind] = dots[dots_pos - 1];
                        curr_ind--;
                        dots_pos--;
                        break;
                    }
                    if (curr_dot.x >= l) {
                        curr_dot.x = 0;
                        if (pos_right == cap_right) {
                            to_right_sq = (dot*) realloc(to_right_sq, sizeof(dot) * cap_right * GROWTH_FACTOR);
                            cap_right *= GROWTH_FACTOR;
                        }
                        to_right_sq[pos_right] = curr_dot;
                        pos_right++;

                        dots[curr_ind] = dots[dots_pos - 1];
                        curr_ind--;
                        dots_pos--;
                        break;
                    }
                    if (curr_dot.y >= l) {
                        curr_dot.y = 0;
                        if (pos_up == cap_up) {
                            to_up_sq = (dot*) realloc(to_up_sq, sizeof(dot) * cap_up * GROWTH_FACTOR);
                            cap_up *= GROWTH_FACTOR;
                        }
                        to_up_sq[pos_up] = curr_dot;
                        pos_up++;

                        dots[curr_ind] = dots[dots_pos - 1];
                        curr_ind--;
                        dots_pos--;
                        break;
                    }
                    if (curr_dot.y < 0) {
                        curr_dot.y = l - 1;
                        if (pos_down == cap_down) {
                            to_down_sq = (dot*) realloc(to_down_sq, sizeof(dot) * cap_down * GROWTH_FACTOR);
                            cap_down *= GROWTH_FACTOR;
                        }
                        to_down_sq[pos_down] = curr_dot;
                        pos_down++;

                        dots[curr_ind] = dots[dots_pos - 1];
                        curr_ind--;
                        dots_pos--;
                        break;
                    }
                } else {
                    if (pos_fin == cap_fin) {
                        finished_dots = (dot*) realloc(finished_dots, sizeof(dot) * cap_fin * GROWTH_FACTOR);
                        cap_fin *= GROWTH_FACTOR;
                    }
                    finished_dots[pos_fin] = curr_dot;
                    pos_fin++;

                    dots[curr_ind] = dots[dots_pos - 1];
                    curr_ind--;
                    dots_pos--;
                    break;
                }
            }
            curr_ind++;
        }
        int pos_from_left, pos_from_right, pos_from_up, pos_from_down;
        MPI_Request* requests_pos = (MPI_Request*) malloc(sizeof(MPI_Request) * 8);

        MPI_Issend(&pos_left, 1, MPI_INT, l_sq_rank, 0, MPI_COMM_WORLD, requests_pos);
        MPI_Issend(&pos_right, 1, MPI_INT, r_sq_rank, 1, MPI_COMM_WORLD, requests_pos + 1);
        MPI_Issend(&pos_up, 1, MPI_INT, u_sq_rank, 2, MPI_COMM_WORLD, requests_pos + 2);
        MPI_Issend(&pos_down, 1, MPI_INT, d_sq_rank, 3, MPI_COMM_WORLD, requests_pos + 3);

        MPI_Irecv(&pos_from_right, 1, MPI_INT, r_sq_rank, 0, MPI_COMM_WORLD, requests_pos + 4);
        MPI_Irecv(&pos_from_left, 1, MPI_INT, l_sq_rank, 1, MPI_COMM_WORLD, requests_pos + 5);
        MPI_Irecv(&pos_from_down, 1, MPI_INT, d_sq_rank, 2, MPI_COMM_WORLD, requests_pos + 6);
        MPI_Irecv(&pos_from_up, 1, MPI_INT, u_sq_rank, 3, MPI_COMM_WORLD, requests_pos + 7);

        MPI_Waitall(8, requests_pos, MPI_STATUS_IGNORE);

        dot* dots_from_left = (dot*) malloc(sizeof(dot) * pos_from_left);
        dot* dots_from_right = (dot*) malloc(sizeof(dot) * pos_from_right);
        dot* dots_from_up = (dot*) malloc(sizeof(dot) * pos_from_up);
        dot* dots_from_down = (dot*) malloc(sizeof(dot) * pos_from_down);

        MPI_Request* request_data = (MPI_Request*) malloc(sizeof(MPI_Request) * 8);
        MPI_Issend(to_left_sq, sizeof(dot) * pos_left, MPI_BYTE, l_sq_rank, 0, MPI_COMM_WORLD, request_data);
        MPI_Issend(to_right_sq, sizeof(dot) * pos_right, MPI_BYTE, r_sq_rank, 1, MPI_COMM_WORLD, request_data + 1);
        MPI_Issend(to_up_sq, sizeof(dot) * pos_up, MPI_BYTE, u_sq_rank, 2, MPI_COMM_WORLD, request_data + 2);
        MPI_Issend(to_down_sq, sizeof(dot) * pos_down, MPI_BYTE, d_sq_rank, 3, MPI_COMM_WORLD, request_data + 3);

        MPI_Irecv(dots_from_right, sizeof(dot) * pos_from_right, MPI_BYTE, r_sq_rank, 0, MPI_COMM_WORLD, request_data + 4);
        MPI_Irecv(dots_from_left, sizeof(dot) * pos_from_left, MPI_BYTE, l_sq_rank, 1, MPI_COMM_WORLD, request_data + 5);
        MPI_Irecv(dots_from_down, sizeof(dot) * pos_from_down, MPI_BYTE, d_sq_rank, 2, MPI_COMM_WORLD, request_data + 6);
        MPI_Irecv(dots_from_up, sizeof(dot) * pos_from_up, MPI_BYTE, u_sq_rank, 3, MPI_COMM_WORLD, request_data + 7);

        MPI_Waitall(8, request_data, MPI_STATUS_IGNORE);

        free(request_data);
        free(requests_pos);

        for (int i = 0; i < pos_from_left; i++) {
            if (dots_cap == dots_pos) {
                dots = (dot*) realloc(dots, sizeof(dot) * dots_cap * GROWTH_FACTOR);
                dots_cap *= GROWTH_FACTOR;
            }
            dots[dots_pos] = dots_from_left[i];
            dots_pos++;
        }
        for (int i = 0; i < pos_from_right; i++) {
            if (dots_cap == dots_pos) {
                dots = (dot*) realloc(dots, sizeof(dot) * dots_cap * GROWTH_FACTOR);
                dots_cap *= GROWTH_FACTOR;
            }
            dots[dots_pos] = dots_from_right[i];
            dots_pos++;
        }
        for (int i = 0; i < pos_from_up; i++) {
            if (dots_cap == dots_pos) {
                dots = (dot*) realloc(dots, sizeof(dot) * dots_cap * GROWTH_FACTOR);
                dots_cap *= GROWTH_FACTOR;
            }
            dots[dots_pos] = dots_from_up[i];
            dots_pos++;
        }
        for (int i = 0; i < pos_from_down; i++) {
            if (dots_cap == dots_pos) {
                dots = (dot*) realloc(dots, sizeof(dot) * dots_cap * GROWTH_FACTOR);
                dots_cap *= GROWTH_FACTOR;
            }
            dots[dots_pos] = dots_from_down[i];
            dots_pos++;
        }

        int total_dots;
        MPI_Reduce(&pos_fin, &total_dots, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);

        int is_finished = 0;
        if (rank == MASTER && total_dots == N * size) {
            is_finished = 1;
        }
        MPI_Bcast(&is_finished, 1, MPI_INT, MASTER, MPI_COMM_WORLD);


        if (is_finished) {
            int* rank_dots = (int*) malloc(sizeof(int) * size);
            MPI_Gather(&pos_fin, 1, MPI_INT, rank_dots, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

            if (rank == MASTER) {
                t2 = MPI_Wtime();

                FILE* output = fopen("stats.txt", "w");
                fprintf(output, "%d %d %d %d %d %f %f %f %f %fs\n", l, a, b, n, N, p_l, p_r, p_u, p_d, t2 - t1);
                for (int i = 0; i < size; i++) {
                    fprintf(output, "%d: %d\n", i, rank_dots[i]);
                }
                fclose(output);
            }
            free(rank_dots);
            free(to_left_sq);
            free(to_right_sq);
            free(to_up_sq);
            free(to_down_sq);
            free(dots);
            free(finished_dots);
            break;
        }

        pos_left = 0;
        pos_right = 0;
        pos_up = 0;
        pos_down = 0;
        MPI_Barrier(MPI_COMM_WORLD);
    }
 }

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int l = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    int n = atoi(argv[4]);
    int N = atoi(argv[5]);

    double p_l = atof(argv[6]);
    double p_r = atof(argv[7]);
    double p_u = atof(argv[8]);
    double p_d = atof(argv[9]);

    random_walk(l, a, b, n, N, p_l, p_r, p_u, p_d, rank, size);
    MPI_Finalize();
    return 0;
}