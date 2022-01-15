#include "container.h"

#include <stdlib.h>

Container *parse_container(FILE *f) {
    Container *res = (Container *) malloc(sizeof(Container));
    if (res == NULL) {
        allocation_error();
        return NULL;
    }
    res->data = (Encryption *) malloc(sizeof(Encryption) * MAX_CONTAINER_SIZE);
    if (res->data == NULL) {
        allocation_error();
        free(res);
        return NULL;
    }
    while (fgetc(f) != EOF) {
        fseek(f, -1, SEEK_CUR);
        if (res->size == MAX_CONTAINER_SIZE) {
            invalid_input();
            destruct_container(res);
            return NULL;
        }
        if (!parse_encrypted(f, res->data + res->size)) {
            destruct_container(res);
            return NULL;
        }
        ++res->size;
        int c = fgetc(f);
        if (c != '\n') {
            invalid_input();
            destruct_container(res);
            return NULL;
        }
    }
    return res;
}

void print_container(Container *container, FILE *f) {
    if (container->size) {
        print_encrypted(container->data[0], f);
        for (size_t i = 1; i < container->size; ++i) {
            fprintf(f, "\n\n");
            print_encrypted(container->data[i], f);
        }
    }
    fprintf(f, "\n");
}

void sort_container(Container *container) {
    Encryption *data = container->data;
    size_t n = container->size;
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = i; j && calculate_key_encrypted(data[j]) < calculate_key_encrypted(data[j - 1]); --j) {
            Encryption temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
        }
    }
}

void destruct_container(Container *container) {
    for (size_t i = 0; i < container->size; ++i) {
        destruct_encrypted(container->data[i]);
    }
    free(container->data);
    free(container);
}