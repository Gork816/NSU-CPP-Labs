#include "pch.h"
#include "C:\Users\79222\Desktop\NSU-CPP-Labs\lab1\bitarray.cpp"

//Constructor tests
TEST(BitArrayTest, DefaultConstructor) {
    BitArray b;
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(BitArrayTest, ConstructorWithParams) {
    BitArray b(10, 0xFFFF);
    EXPECT_EQ(b.size(), 10);
    EXPECT_TRUE(b.any());
    EXPECT_EQ(b.count(), 10);

    BitArray a(5, 0b01011);
    EXPECT_EQ(a.to_string(), "01011");
    EXPECT_TRUE(a[4]);
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray b1(10, 0xAAAA);
    BitArray b2(b1);
    EXPECT_EQ(b1, b2);
}

//operator=
TEST(BitArrayTest, AssignmentOperator) {
    BitArray b1(8, 0xFF);
    BitArray b2;
    b2 = b1;
    EXPECT_EQ(b1, b2);
}

//operator[]
TEST(BitArrayTest, BitAccess) {
    BitArray b(5, 0b00111);
    EXPECT_FALSE(b[0]);
    EXPECT_FALSE(b[1]);
    EXPECT_TRUE(b[2]);
    b[2] = false;
    EXPECT_FALSE(b[2]);
}

//to_string()
TEST(BitArrayTest, ToString) {
    BitArray b(5, 0x1C);
    EXPECT_EQ(b.to_string(), "11100");
    EXPECT_TRUE(b[2]);
}

//set()
TEST(BitArrayTest, SetBit) {
    BitArray b(5);
    EXPECT_EQ(b.to_string(), "00000");
    b.set(3);
    EXPECT_TRUE(b[3]);
    EXPECT_EQ(b.to_string(), "00010");
    b.set(3, false);
    EXPECT_FALSE(b[3]);
}

//reset()
TEST(BitArrayTest, ResetBit) {
    BitArray b(5, 0b11111);
    b.reset(2);
    EXPECT_FALSE(b[2]);
    b.reset();
    EXPECT_TRUE(b.none());
}

//swap()
TEST(BitArrayTest, Swap) {
    BitArray b1(10, 0x1F);
    BitArray b2(10, 0x5555);
    b1.swap(b2);
    EXPECT_EQ(b1.count(), 5);
    EXPECT_EQ(b2.count(), 5);
}

//resize()
TEST(BitArrayTest, Resize) {
    BitArray b(5, 0xFFFF);
    b.resize(10, true);
    EXPECT_EQ(b.size(), 10);
    EXPECT_EQ(b.count(), 10);

    b.resize(8);
    EXPECT_EQ(b.count(), 8);
}

//clear()
TEST(BitArrayTest, Clear) {
    BitArray b(10, 0xFFFF);
    b.clear();
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

//push_back
TEST(BitArrayTest, PushBack) {
    BitArray b;
    b.push_back(true);
    EXPECT_EQ(b.size(), 1);
    EXPECT_TRUE(b[0]);
}

//operator&=
TEST(BitArrayTest, BitwiseAnd) {
    BitArray b1(5, 0b11011);
    BitArray b2(5, 0b10101);
    b1 &= b2;
    EXPECT_EQ(b1.to_string(), "10001");
}

//operator|=
TEST(BitArrayTest, BitwiseOr) {
    BitArray b1(5, 0b11011);
    BitArray b2(5, 0b10101);
    b1 |= b2;
    EXPECT_EQ(b1.to_string(), "11111");
}

//operator^=
TEST(BitArrayTest, BitwiseXor) {
    BitArray b1(5, 0b11011);
    BitArray b2(5, 0b10101);
    b1 ^= b2;
    EXPECT_EQ(b1.to_string(), "01110");
}

//operator<<=
TEST(BitArrayTest, LeftShift) {
    BitArray b(5, 0b10011);
    b <<= 2;
    EXPECT_EQ(b.to_string(), "01100");
}

//operator>>=
TEST(BitArrayTest, RightShift) {
    BitArray b(5, 0b11001);
    b >>= 2;
    EXPECT_EQ(b.to_string(), "00110");
}

//any(), none()
TEST(BitArrayTest, AnyAndNone) {
    BitArray b(5, 0b00001);
    EXPECT_TRUE(b.any());
    b.reset();
    EXPECT_TRUE(b.none());
}

//operator~
TEST(BitArrayTest, BitwiseNot) {
    BitArray b(5, 0b10101);
    BitArray b_not = ~b;
    EXPECT_EQ(b_not.to_string(), "01010");
}

//count()
TEST(BitArrayTest, CountBits) {
    BitArray b(5, 0b11011);
    EXPECT_EQ(b.count(), 4);
}

//operator==
TEST(BitArrayTest, EqualityOperator) {
    BitArray b1(5, 0b10101);
    BitArray b2(5, 0b10101);
    EXPECT_TRUE(b1 == b2);
}

//operator!=
TEST(BitArrayTest, InequalityOperator) {
    BitArray b1(5, 0b10101);
    BitArray b2(5, 0b11111);
    EXPECT_TRUE(b1 != b2);
}

//begin(), end()
TEST(BitArrayIteratorTest, BeginAndEnd) {
    BitArray b(10, 0b1010101010);

    auto it_begin = b.begin();
    auto it_end = b.end();

    EXPECT_TRUE(it_begin != it_end); 
    EXPECT_TRUE(*it_begin);
}

//operator++
TEST(BitArrayIteratorTest, Increment) {
    BitArray b(10, 0b1010101010);
    auto it = b.begin();

    ++it;
    EXPECT_EQ(*it, false); 

    it++;
    EXPECT_EQ(*it, true); 
}

//operator--
TEST(BitArrayIteratorTest, Decrement) {
    BitArray b(10, 0b1010101010);
    auto it = b.end();
    --it; 
    EXPECT_EQ(*it, false); 

    it--;
    EXPECT_EQ(*it, true); 
}

//operator==, !=
TEST(BitArrayIteratorTest, Comparison) {
    BitArray b(10, 0b1010101010);
    auto it1 = b.begin();
    auto it2 = b.begin();
    auto it_end = b.end();

    EXPECT_EQ(it1 == it2, true);    
    EXPECT_EQ(it1 != it_end, true); 

    ++it1;
    EXPECT_EQ(it1 != it2, true); 
}

//operator*
TEST(BitArrayIteratorTest, Dereference) {
    BitArray b(10, 0b1010101010);
    auto it = b.begin();

    EXPECT_EQ(*it, true);

    ++it;
    EXPECT_EQ(*it, false);

    ++it;
    EXPECT_EQ(*it, true);
}

//test for empty iterator
TEST(BitArrayIteratorTest, EmptyArray) {
    BitArray b;
    auto it_begin = b.begin();
    auto it_end = b.end();

    EXPECT_EQ(it_begin == it_end, true);

    EXPECT_THROW(*it_begin, std::out_of_range);
}

//full iterator test
TEST(BitArrayIteratorTest, FullIteration) {
    BitArray b(10, 0b1010101010);
    std::string result;

    for (auto it = b.begin(); it != b.end(); ++it) {
        result += (*it ? "1" : "0");
    }

    EXPECT_EQ(result, "1010101010");
}

//full iterator test
TEST(BitArrayIteratorTest, FullIteration2) {
    BitArray b(10, 0b1010101010);
    std::string result;

    for (auto it: b) {
        result += (it ? "1" : "0");
    }

    EXPECT_EQ(result, "1010101010");
}