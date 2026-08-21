#include "BitVector.h"
#include <iostream>

BitVector::BitVector(int n) {
    size = n;
    int blocks = n / 64 + (n % 64 ? 1 : 0);
    b_vector_data.assign(blocks, 0);
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

bool BitVector::intersectionNotEmpty(BitVector& b) {
    bool result = false;
    for (int i = 0; i < b_vector_data.size(); i++) {
        result |= ((b_vector_data[i] & b.b_vector_data[i]) != 0);
    }
    return result;
}

void BitVector::intersect(BitVector& b) {
    for (int i = 0; i < b_vector_data.size(); i++) {
        b_vector_data[i] &= b.b_vector_data[i];
    }
    return;
}

void BitVector::mask(int index) {
    int block = index / 64;
    int block_index = index % 64;
    b_vector_data[block] &= (1ULL << block_index);
    return;
}

bool BitVector::isZero() {
    int s = b_vector_data.size();
    for (int i = 0; i < s; i++) {
        if (b_vector_data[i]){return 0;}
    }
    return 1;
}

int BitVector::nextOnePosition(int pos) {
    if (pos > size - 1) {return -1;}
    int block_index = pos / 64;
    int block_position = pos % 64;
    while (block_index < b_vector_data.size()) {
        if ((b_vector_data[block_index] & ((~0ULL) << (block_position+1))) != 0) {
            return __builtin_ctzll(b_vector_data[block_index] & ((~0ULL) << (block_position+1))) + 64*block_index;
        }
        block_index++;
    }
    return -1;
}