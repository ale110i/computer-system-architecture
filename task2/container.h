#pragma once

#include "common.h"
#include "encryption.h"

#include <cstdio>

class Container {
public:
    Container();

    void Parse(FILE *f);

    void Print(FILE *f) const;

    void Sort();

    [[nodiscard]] size_t GetSize() const;

    ~Container();

private:
    Encryption **data = nullptr;
    size_t size = 0;
};
