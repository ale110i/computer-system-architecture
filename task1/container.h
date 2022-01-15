#pragma once

#include "common.h"
#include "encryption.h"

#include <stdio.h>

typedef struct Container {
    size_t size;
    Encryption *data;
} Container;

Container *parse_container(FILE *f);

void print_container(Container *container, FILE *f);

void sort_container(Container *container);

void destruct_container(Container *container);

