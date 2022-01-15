#pragma once

#include <cstdio>

class Encryption {
public:
    Encryption() = default;

    virtual void Parse(FILE *f) = 0;

    [[nodiscard]] double GetKey() const;

    virtual void Print(FILE *f) const = 0;

    virtual ~Encryption() = default;

protected:
    double key = 0;
};
