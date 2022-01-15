#pragma once

#include "common.h"
#include "encryption.h"

#include <cstdio>

class CharactersReplacementEncryption : public Encryption {
public:
    CharactersReplacementEncryption() = default;

    void Parse(FILE *f) override;

    void Print(FILE *f) const override;

    ~CharactersReplacementEncryption() override;

private:
    struct CharReplacement {
        char original;
        char replacement;
    };

    CharReplacement *replacement = nullptr;
    int replacement_size = 0;
    char *encrypted_string = nullptr;
};
