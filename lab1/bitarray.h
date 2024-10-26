#pragma once

#include <vector>
#include <string>

class BitArray {
private:
    std::vector<bool> bits;

public:
    BitArray();
    ~BitArray();

    explicit BitArray(int num_bits, unsigned long value = 0);
    BitArray(const BitArray& b);

    void swap(BitArray& b);

    BitArray& operator=(const BitArray& b);

    int size() const;
    bool empty() const;
    bool any() const;
    bool none() const;
    int count() const;

    BitArray operator~() const;

    void resize(int num_bits, bool value = false);
    void clear();
    void push_back(bool bit);

    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);
};