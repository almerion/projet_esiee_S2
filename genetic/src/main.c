#include "matrix.h"
#include "parser.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "You have to specify the path to a csv as argument\n");
        return 1;
    }

    Matrix* m = parse_file(argv[1]);
    if (m == NULL) {
        return 2;
    }

    display_matrix(m);
    printf("\n%d\n",m->size);
    free_matrix(m);
    return 0;
}