#include "container.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid parameters\n");
        return 0;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Can't open input file\n");
        return 0;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Can't open output file\n");
        return 0;
    }

    Container *container = parse_container(input);
    if (container == NULL) {
        return 0;
    }
    fclose(input);

    fprintf(output, "Container size: %lu\n", container->size);
    if (container->size) {
        fprintf(output, "\nINITIAL ORDER:\n\n");
        print_container(container, output);
        sort_container(container);
        fprintf(output, "\nSORTED:\n\n");
        print_container(container, output);
    }
    fclose(output);
    destruct_container(container);
    return 0;
}
