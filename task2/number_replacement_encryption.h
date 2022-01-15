#pragma once

#include "common.h"
#include "encryption.h"

class NumberReplacementEncryption : public Encryption {
public:
    NumberReplacementEncryption() = default;

    void Parse(FILE *f) override;

    void Print(FILE *f) const override;

    ~NumberReplacementEncryption() override;

private:
    struct NumberReplacement {
        char original;
        short replacement;
    };
    NumberReplacement *replacement = nullptr;
    short *encrypted_string = nullptr;
    size_t string_len = 0;
    int replacement_size = 0;
};
