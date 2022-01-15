#include "container.h"

#include <cstdio>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid parameters\n");
        return 0;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        printf("Can't open input file\n");
        return 0;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == nullptr) {
        printf("Can't open output file\n");
        return 0;
    }

    Container container;
    try {
        container.Parse(input);
    } catch (...) {
        invalid_input();
        fclose(input);
        fclose(output);
        return 0;
    }
    fprintf(output, "Container size: %lu\n", container.GetSize());
    if (container.GetSize()) {
        fprintf(output, "\nINITIAL ORDER:\n\n");
        container.Print(output);
        container.Sort();
        fprintf(output, "\nSORTED:\n\n");
        container.Print(output);
    }
    fclose(output);
    return 0;
}
