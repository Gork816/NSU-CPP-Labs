#include "bitarray.h"
#include <stdexcept>
#include <algorithm>

BitArray::BitArray() = default;

BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value) {
    bits.resize(num_bits);
    for (int i = 0; i < std::min(num_bits, (int)(sizeof(long) * 8)); ++i) {
        bits[i] = (value >> i) & 1;
    }
}

BitArray::BitArray(const BitArray& b) : bits(b.bits) {}

void BitArray::swap(BitArray& b) {
    bits.swap(b.bits);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        bits = b.bits;
    }
    return *this;
}


int BitArray::size() const {
    return bits.size();
}

bool BitArray::empty() const {
    return bits.empty();
}

bool BitArray::any() const {
    return std::any_of(bits.begin(), bits.end(), [](bool b) { return b; });
}

bool BitArray::none() const {
    return std::none_of(bits.begin(), bits.end(), [](bool b) { return b; });
}

int BitArray::count() const {
    return std::count(bits.begin(), bits.end(), true);
}


BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (size_t i = 0; i < result.bits.size(); ++i) {
        result.bits[i] = !result.bits[i];
    }
    return result;
}


void BitArray::resize(int num_bits, bool value) {
    bits.resize(num_bits, value);
}

void BitArray::clear() {
    bits.clear();
}

void BitArray::push_back(bool bit) {
    bits.push_back(bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (bits.size() != b.bits.size()) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] = static_cast<bool>(bits[i] & b.bits[i]);
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (bits.size() != b.bits.size()) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] = static_cast<bool>(bits[i] | b.bits[i]);
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (bits.size() != b.bits.size()) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] = static_cast<bool>(bits[i] ^ b.bits[i]);
    }
    return *this;
}