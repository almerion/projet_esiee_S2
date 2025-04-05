#include "parser.h"
#include "matrix.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>

/* Returns the number of distimes assigned or -1 if there's a problem*/
int parse_line(Distime* distimes, char* line) {
    int i;
    char *token = strtok(line, ",");
    
    for(i = 0; token != NULL; i++) {
        int result = sscanf(token, "%f:%d", &distimes[i].dist, &distimes[i].time);
        if(result != 2) {
            fprintf(stderr, "Invalid distance time : \"%s\"\n", token);
            return -1;
        }
        token = strtok(NULL, ",");
    }

    return i;
}

int read_line(FILE *file, char *buffer, int buffer_size)
{
    if (file == NULL || buffer == NULL || buffer_size < 2) {
        return -1;
    }

    int c;
    int i = 0;

    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (i < buffer_size - 1) {
            buffer[i++] = (char)c;
        } else {
            return -1;
        }
    }

    buffer[i] = '\0';
    return 1;
}

/* Reads the first line to prepare the matrix */
Matrix* prepare_matrix(FILE *file, char *line_buffer) {
    Distime *distime_buffer = create_distime(DISTIME_BUFFER_SIZE);
    read_line(file, line_buffer, LINE_BUFFER_SIZE);
    
    int nb_lines = parse_line(distime_buffer, line_buffer);
    if(nb_lines <= 0) {
        free(distime_buffer);
        return NULL;
    }

    distime_buffer = (Distime*) realloc(distime_buffer, sizeof(Distime) * nb_lines);
    if(distime_buffer == NULL) {
        free(distime_buffer);
        fprintf(stderr, "realloc of distime buffer failed\n");
        return NULL;
    }

    return create_matrix(nb_lines, distime_buffer);
}

Matrix* parse_file(char* filePath) {
    FILE* file = fopen(filePath, "r");

    if ( file == NULL ) {
        fprintf(stderr, "Cannot open file %s\n", filePath);
        return NULL;
    }

    char *buffer = (char*) malloc(sizeof(char) * LINE_BUFFER_SIZE);
    Matrix *matrix = prepare_matrix(file, buffer);
    if(matrix == NULL) {
        free(buffer);
        fclose(file);
        return NULL;
    };

    int i = 1;
    while (!feof(file)) {
        if(!read_line(file, buffer, LINE_BUFFER_SIZE)) {
            free_matrix(matrix);
            fprintf(stderr, "Something went wrong while reading the line number %d\n", i+1);
            fclose(file);
            free(buffer);
            return NULL;
        }
        if(buffer[0] == '\0') continue;
        
        if(parse_line(matrix->matrix[i], buffer) != matrix->size) {
            free_matrix(matrix);
            fprintf(stderr, "Something went wrong while parsing the line number %d\n", i+1);
            fclose(file);
            free(buffer);
            return NULL;
        }
        i++;
    }

    free(buffer);
    fclose(file);
    return matrix;
}