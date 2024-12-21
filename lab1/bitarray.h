#pragma once

#include <vector>
#include <string>


class BitArray {
public:

    static constexpr int BITS_PER_BLOCK = sizeof(unsigned long) * 8;

    /**
     * @class reference
     * Proxy class to allow for setting and accessing individual bits in the array.
     * Provides assignment operators and boolean conversion for convenient bit manipulation.
     */
    class reference {
        friend class BitArray;

    public:
        /**
         * Converts the reference to a boolean.
         * @return The value of the bit as a bool (true if set, false otherwise).
         */
        operator bool() const;

        /**
         * Assigns a boolean value to the referenced bit.
         * @param value Boolean value to set (true or false).
         * @return Reference to the modified object.
         */
        reference& operator=(bool value);

        /**
         * Assigns the value of another reference.
         * @param other Another reference object to copy from.
         * @return Reference to the modified object.
         */
        reference& operator=(const reference& other);

    private:
        reference(BitArray* array, int index);
        BitArray* array;
        int index;
    };

    /**
     * Default constructor. Creates an empty BitArray.
     */
    BitArray();

    /**
     * Constructs a BitArray with a specified number of bits.
     * Optionally initializes the first bits with a given value.
     * @param num_bits Number of bits in the array.
     * @param value Optional unsigned long value for initial bits.
     */
    explicit BitArray(int num_bits, unsigned long value = 0);

    /**
     * Copy constructor.
     * @param b BitArray to copy from.
     */
    BitArray(const BitArray& b);

    /**
     * Destructor. Cleans up allocated resources.
     */
    ~BitArray();

    /**
     * Swaps the contents of this BitArray with another.
     * @param b BitArray to swap with.
     */
    void swap(BitArray& b);

    /**
     * Assignment operator.
     * @param b BitArray to assign from.
     * @return Reference to the modified object.
     */
    BitArray& operator=(const BitArray& b);

    /**
     * Resizes the bit array to a new size. New bits are initialized with a specified value.
     * @param num_bits New size of the array.
     * @param value Value to initialize new bits (if expanded).
     */
    void resize(int num_bits, bool value = false);

    /**
     * Clears all bits in the array and resets its size to zero.
     */
    void clear();

    /**
     * Appends a new bit to the end of the array.
     * Expands storage if necessary.
     * @param bit Boolean value of the new bit.
     */
    void push_back(bool bit);

    /**
     * Performs a bitwise AND operation with another BitArray of the same size.
     * @param b BitArray to AND with.
     * @return Reference to the modified object.
     * @throws std::invalid_argument if arrays have different sizes.
     */
    BitArray& operator&=(const BitArray& b);

    /**
     * Performs a bitwise OR operation with another BitArray of the same size.
     * @param b BitArray to OR with.
     * @return Reference to the modified object.
     * @throws std::invalid_argument if arrays have different sizes.
     */
    BitArray& operator|=(const BitArray& b);

    /**
     * Performs a bitwise XOR operation with another BitArray of the same size.
     * @param b BitArray to XOR with.
     * @return Reference to the modified object.
     * @throws std::invalid_argument if arrays have different sizes.
     */
    BitArray& operator^=(const BitArray& b);

    /**
     * Left-shifts the bits in the array by a specified amount.
     * Zero-fills the bits shifted in from the right.
     * @param n Number of positions to shift.
     * @return Reference to the modified object.
     */
    BitArray& operator<<=(int n);

    /**
     * Right-shifts the bits in the array by a specified amount.
     * Zero-fills the bits shifted in from the left.
     * @param n Number of positions to shift.
     * @return Reference to the modified object.
     */
    BitArray& operator>>=(int n);

    /**
     * Returns a new BitArray with bits left-shifted by a specified amount.
     * @param n Number of positions to shift.
     * @return Shifted BitArray.
     */
    BitArray operator<<(int n) const;

    /**
     * Returns a new BitArray with bits right-shifted by a specified amount.
     * @param n Number of positions to shift.
     * @return Shifted BitArray.
     */
    BitArray operator>>(int n) const;

    /**
     * Accesses a specific bit in the array.
     * Provides a modifiable reference to the bit.
     * @param i Index of the bit.
     * @return Reference to the bit at index i.
     * @throws std::out_of_range if index is invalid.
     */
    reference operator[](int i);

    /**
     * Accesses a specific bit in the array (const version).
     * @param i Index of the bit.
     * @return Boolean value of the bit at index i.
     * @throws std::out_of_range if index is invalid.
     */
    bool operator[](int i) const;

    /**
     * Sets a specific bit to a given value.
     * @param n Index of the bit to set.
     * @param val Value to set (true or false).
     * @return Reference to the modified object.
     * @throws std::out_of_range if index is invalid.
     */
    BitArray& set(int n, bool val = true);

    /**
     * Sets all bits in the array to true.
     * @return Reference to the modified object.
     */
    BitArray& set();

    /**
     * Resets (clears) a specific bit to false.
     * @param n Index of the bit to reset.
     * @return Reference to the modified object.
     * @throws std::out_of_range if index is invalid.
     */
    BitArray& reset(int n);

    /**
     * Resets all bits in the array to false.
     * @return Reference to the modified object.
     */
    BitArray& reset();

    /**
     * Checks if any bits are set to true.
     * @return True if any bits are true, false otherwise.
     */
    bool any() const;

    /**
     * Checks if all bits are set to false.
     * @return True if all bits are false, false otherwise.
     */
    bool none() const;

    /**
     * Bitwise NOT operation. Returns a new BitArray with inverted bits.
     * @return BitArray with all bits inverted.
     */
    BitArray operator~() const;

    /**
     * Counts the number of bits set to true.
     * @return The count of true bits in the array.
     */
    int count() const;

    /**
     * Returns the total number of bits in the array.
     * @return Size of the BitArray.
     */
    int size() const;

    /**
     * Checks if the BitArray is empty.
     * @return True if array size is zero, false otherwise.
     */
    bool empty() const;

    /**
     * Returns a string representation of the bits in the array.
     * @return String representation of the BitArray, with bits in binary form.
     */
    std::string to_string() const;

    /**
     * Equality operator. Compares two BitArrays for equality.
     * @param a First BitArray.
     * @param b Second BitArray.
     * @return True if arrays are equal, false otherwise.
     */
    friend bool operator==(const BitArray& a, const BitArray& b);

    /**
     * Inequality operator. Compares two BitArrays for inequality.
     * @param a First BitArray.
     * @param b Second BitArray.
     * @return True if arrays are not equal, false otherwise.
     */
    friend bool operator!=(const BitArray& a, const BitArray& b);

    /**
     * @class Iterator
     * @brief Provides an iterator interface for traversing through a BitArray.
     * This class is designed to iterate over the bits in a BitArray,
     * allowing read-only access to the individual bits using the dereference operator.
     */
    class Iterator {
    public:
        /**
         * @brief Constructs an Iterator object.
         * @param bit_array Pointer to the BitArray being iterated over.
         * @param index The starting index of the iterator within the BitArray.
         */
        Iterator(const BitArray* bit_array, int index);

        /**
         * @brief Dereferences the iterator to access the current bit.
         * @return The value of the bit at the current position (true for 1, false for 0).
         * @throws std::out_of_range If the iterator is out of the valid range.
         */
        bool operator*() const;

        /**
         * @brief Pre-increment operator. Moves the iterator to the next bit.
         * @return A reference to the updated iterator.
         */
        Iterator& operator++();

        /**
         * @brief Post-increment operator. Moves the iterator to the next bit.
         * @return A copy of the iterator before incrementing.
         */
        Iterator operator++(int);

        /**
         * @brief Pre-decrement operator. Moves the iterator to the previous bit.
         * @return A reference to the updated iterator.
         */
        Iterator& operator--();

        /**
         * @brief Post-decrement operator. Moves the iterator to the previous bit.
         * @return A copy of the iterator before decrementing.
         */
        Iterator operator--(int);

        /**
         * @brief Compares two iterators for equality.
         * @param other The iterator to compare with.
         * @return True if the iterators point to the same position in the same BitArray.
         */
        bool operator==(const Iterator& other) const;

        /**
         * @brief Compares two iterators for inequality.
         * @param other The iterator to compare with.
         * @return True if the iterators point to different positions or different BitArrays.
         */
        bool operator!=(const Iterator& other) const;

    private:
        const BitArray* bit_array;
        int index;
    };

    /**
     * @brief Returns an iterator to the beginning of the BitArray.
     * @return An iterator pointing to the first bit of the BitArray.
     */
    Iterator begin() const;

    /**
     * @brief Returns an iterator to the end of the BitArray.
     * @return An iterator pointing one position past the last bit of the BitArray.
     */
    Iterator end() const;


private:
    int num_bits;
    std::vector<unsigned long> bits;
};

/**
 * Bitwise AND operator for two BitArrays.
 * @param b1 First BitArray.
 * @param b2 Second BitArray.
 * @return New BitArray representing the AND operation.
 */
BitArray operator&(const BitArray& b1, const BitArray& b2);

/**
 * Bitwise OR operator for two BitArrays.
 * @param b1 First BitArray.
 * @param b2 Second BitArray.
 * @return New BitArray representing the OR operation.
 */
BitArray operator|(const BitArray& b1, const BitArray& b2);

/**
 * Bitwise XOR operator for two BitArrays.
 * @param b1 First BitArray.
 * @param b2 Second BitArray.
 * @return New BitArray representing the XOR operation.
 */
BitArray operator^(const BitArray& b1, const BitArray& b2);