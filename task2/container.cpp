#include "container.h"
#include "characters_replacement_encryption.h"
#include "shift_encryption.h"
#include "number_replacement_encryption.h"

#include <stdexcept>


Container::Container() {
    data = new Encryption *[MAX_CONTAINER_SIZE];
}

void Container::Parse(FILE *f) {
    while (fgetc(f) != EOF) {
        fseek(f, -1, SEEK_CUR);
        if (size == MAX_CONTAINER_SIZE) {
            throw std::invalid_argument("");
        }
        int type_id;
        if (fscanf(f, "%d", &type_id) != 1 || type_id < 1 || type_id > 3) {
            throw std::invalid_argument("");
        }
        if (type_id == 1) {
            data[size] = new CharactersReplacementEncryption();
            data[size]->Parse(f);
        } else if (type_id == 2) {
            data[size] = new ShiftEncryption();
            data[size]->Parse(f);
        } else if (type_id == 3) {
            data[size] = new NumberReplacementEncryption();
            data[size]->Parse(f);
        }
        ++size;
        int c = fgetc(f);
        if (c != '\n') {
            throw std::invalid_argument("");
        }
    }
}

void Container::Print(FILE *f) const {
    if (!data) {
        return;
    }
    if (size) {
        data[0]->Print(f);
        for (size_t i = 1; i < size; ++i) {
            fprintf(f, "\n\n");
            data[i]->Print(f);
        }
    }
    fprintf(f, "\n");
}

Container::~Container() {
    if (!data) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    data = nullptr;
}

void Container::Sort() {
    if (!data) {
        return;
    }
    for (size_t i = 1; i < size; ++i) {
        for (size_t j = i; j && data[j]->GetKey() < data[j - 1]->GetKey(); --j) {
            std::swap(data[j], data[j - 1]);
        }
    }
}

size_t Container::GetSize() const {
    return size;
}
