#include "BitVector.h"
#include <iostream>

BitVector::BitVector(int n) {
    int blocks = n / 64 + (n % 64 ? 1 : 0);
    b_vector_data.assign(blocks, 0);
}

bool BitVector::getElement(int index) {
    int block = index / 64;
    int block_index = index % 64;
    return  (b_vector_data[block] & (1ULL << block_index)) != 0;
}

void BitVector::setOne(int index) {
    int block = index / 64;
    int block_index = index % 64;
    b_vector_data[block] |= (1ULL << block_index);
    return;
}

void BitVector::setZero(int index) {
    int block = index / 64;
    int block_index = index % 64;
    b_vector_data[block] &= ~(1ULL << block_index);
    return;
}

bool BitVector::intersect(BitVector& b) {
    bool result = false;
    for (int i = 0; i < b_vector_data.size(); i++) {
        result |= ((b_vector_data[i] & b.b_vector_data[i]) != 0);
    }
    return result;
}