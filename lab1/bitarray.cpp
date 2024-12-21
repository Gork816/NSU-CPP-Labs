#include "BitArray.h"
#include <stdexcept>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <iostream>

BitArray::reference::reference(BitArray* array, int index) : array(array), index(index) {}

BitArray::reference::operator bool() const {
    return (array->bits[index / (BITS_PER_BLOCK)] & (1UL << (index % (BITS_PER_BLOCK)))) != 0;
}

BitArray::reference& BitArray::reference::operator=(bool value) {
    if (value) {
        array->bits[index / (BITS_PER_BLOCK)] |= (1UL << (index % (BITS_PER_BLOCK)));
    }
    else {
        array->bits[index / (BITS_PER_BLOCK)] &= ~(1UL << (index % (BITS_PER_BLOCK)));
    }
    return *this;
}

BitArray::reference& BitArray::reference::operator=(const reference& other) {
    *this = static_cast<bool>(other);
    return *this;
}

BitArray::BitArray() : num_bits(0) {}

BitArray::BitArray(int num_bits, unsigned long value) : num_bits(num_bits) {
    int num_blocks = (num_bits + BITS_PER_BLOCK - 1) / (BITS_PER_BLOCK);
    bits.resize(num_blocks, 0);
    if (num_bits > 0) {
        bits[0] = value;
    }
}

BitArray::BitArray(const BitArray& b) : num_bits(b.num_bits), bits(b.bits) {}

BitArray::~BitArray() {}

void BitArray::swap(BitArray& b) {
    std::swap(num_bits, b.num_bits);
    std::swap(bits, b.bits);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        num_bits = b.num_bits;
        bits = b.bits;
    }
    return *this;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= num_bits) throw std::out_of_range("Index out of range");
    int reversed_index = num_bits - 1 - i;
    return (bits[reversed_index / (BITS_PER_BLOCK)] & (1UL << (reversed_index % (BITS_PER_BLOCK)))) != 0;
}

BitArray::reference BitArray::operator[](int i) {
    if (i < 0 || i >= num_bits) throw std::out_of_range("Index out of range");
    int reversed_index = num_bits - 1 - i;
    return reference(this, reversed_index);
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= num_bits) {
        throw std::out_of_range("Index out of range");
    }
    (*this)[n] = val;
    return *this;
}

BitArray& BitArray::set() {
    std::fill(bits.begin(), bits.end(), ~0);
    return *this;
}

BitArray& BitArray::reset(int n) {
    return set(n, false);
}

BitArray& BitArray::reset() {
    std::fill(bits.begin(), bits.end(), 0);
    return *this;
}

void BitArray::resize(int new_num_bits, bool value) {
    if (new_num_bits < 0) throw std::invalid_argument("Negative size not allowed.");
    if (new_num_bits != num_bits) {
        int old_num_bits = num_bits;
        num_bits = new_num_bits;
        int num_longs = (new_num_bits + BITS_PER_BLOCK - 1) / (BITS_PER_BLOCK);
        bits.resize(num_longs);
        if (new_num_bits > old_num_bits) {
            for (int i = old_num_bits; i < new_num_bits; ++i) {
                set(i, value);
            }
        }
    }
}

void BitArray::clear() {
    num_bits = 0;
    bits.clear();
}

void BitArray::push_back(bool bit) {
    resize(num_bits + 1);
    set(num_bits - 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (num_bits != b.num_bits) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (num_bits != b.num_bits) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (num_bits != b.num_bits) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] ^= b.bits[i];
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    if (n <= 0) return *this;
    BitArray result(*this);
    for (int i = 0; i < num_bits - n; ++i) {
        result.set(i, (*this)[i + n]);
    }
    for (int i = num_bits - n; i < num_bits; ++i) {
        result.set(i, false);
    }
    return result;
}

BitArray BitArray::operator>>(int n) const {
    if (n <= 0) return *this;

    BitArray result(*this);
    for (int i = num_bits - 1; i >= n; --i) {
        result.set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        result.set(i, false);
    }
    return result;
}

BitArray& BitArray::operator<<=(int n) {
    *this = *this << n;
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    *this = *this >> n;
    return *this;
}

bool BitArray::any() const {
    for (auto bitset : bits) {
        if (bitset != 0) return true;
    }
    return false;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (auto& bitset : result.bits) {
        bitset = ~bitset;
    }
    return result;
}

int BitArray::count() const {
    int bit_count = 0;
    int remaining_bits = num_bits;

    for (size_t i = 0; i < bits.size() && remaining_bits > 0; ++i) {
        unsigned long block = bits[i];

        if (remaining_bits < BITS_PER_BLOCK) {
            block &= (1UL << remaining_bits) - 1;
        }

        bit_count += std::bitset<BITS_PER_BLOCK>(block).count();
        remaining_bits -= BITS_PER_BLOCK;
    }

    return bit_count;
}

int BitArray::size() const {
    return num_bits;
}

bool BitArray::empty() const {
    return num_bits == 0;
}

std::string BitArray::to_string() const {
    std::string str;
    for (int i = 0; i < num_bits; ++i) {
        str += (*this)[i] ? '1' : '0';
    }
    return str;
}

bool operator==(const BitArray& a, const BitArray& b) {
    return a.num_bits == b.num_bits && a.bits == b.bits;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result ^= b2;
    return result;
}

BitArray::Iterator::Iterator(const BitArray* bit_array, int index)
    : bit_array(bit_array), index(index) {}

bool BitArray::Iterator::operator*() const {
    if (!bit_array || index < 0 || index >= bit_array->num_bits) {
        throw std::out_of_range("Iterator out of bounds");
    }
    return (*bit_array)[index];
}

BitArray::Iterator& BitArray::Iterator::operator++() {
    if (index < bit_array->num_bits) {
        ++index;
    }
    return *this;
}

BitArray::Iterator BitArray::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

BitArray::Iterator& BitArray::Iterator::operator--() {
    if (index > 0) {
        --index;
    }
    return *this;
}

BitArray::Iterator BitArray::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

bool BitArray::Iterator::operator==(const Iterator& other) const {
    return bit_array == other.bit_array && index == other.index;
}

bool BitArray::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

BitArray::Iterator BitArray::begin() const {
    return Iterator(this, 0);
}

BitArray::Iterator BitArray::end() const {
    return Iterator(this, num_bits);
}