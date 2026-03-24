#pragma once
#include <cstdint>
#include <vector>

// BitVector is our simple custom implemented datatype for using full potential of Ullman's algorithm with bitwise operations.
// we use it in the refinement procedure 

class BitVector{

public:
    BitVector(int n); 
    bool getElement(int index);
    void setOne(int index);
    void setZero(int index);
    bool intersect(BitVector& b);

//private:
    std::vector<uint64_t> b_vector_data; // we use largest possible size of integer
};