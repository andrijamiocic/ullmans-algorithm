#pragma once
#include <cstdint>
#include <vector>

// BitVector is our simple custom implemented datatype for using full potential of Ullman's algorithm with bitwise operations.
// we use it in the refinement procedure 

class BitVector{

public:
    BitVector(int n); // constuctor - n is the number of stored bits, all assigned 0
    bool getElement(int index) {
        int block = index / 64;
        int block_index = index % 64;
        return  (b_vector_data[block] & (1ULL << block_index)) != 0;
    }
    void setOne(int index);
    void setZero(int index);
    bool intersectionNotEmpty(BitVector& b); 
    void intersect(BitVector& b);
    void mask(int index);
    bool isZero();
    int nextOnePosition(int pos);

private:
    std::vector<uint64_t> b_vector_data; // we use largest possible size of integer
    int size;
};