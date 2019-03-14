#define MATRIX_SIZE 4
//stores the 3 matrixes and the start and end time of all the procsses, although end can hold up to 4 elements, not all are used.
struct Matrix{
    int M[MATRIX_SIZE][MATRIX_SIZE];
    int N[MATRIX_SIZE][MATRIX_SIZE];
    int Q[MATRIX_SIZE][MATRIX_SIZE];
    struct timeval start, end[4];
};
