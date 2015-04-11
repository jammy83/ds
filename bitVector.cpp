//
//  bitVector.cpp
//  
//
//  Created by Janani Natarajan on 12/31/14.
//
//

#include <iostream>

class bitVector {
 private:
    int* bitSet;              // space for the bitMap
    static int SHIFT 5        // 32 = 2^5
    static int BITSPERWORD 32 // bits of int, depends on the computer
    static int MASK 0x1F;     // 11111 in binary

 public:
    bitVector(int size) {
        bitSet = new int[size/BITSPERWORD + 1];
    }
    ~bitVector();
    void set(int i) {
        int wordNumber = (i >> SHIFT); // divide by 32
        int bitNumber = (i & MASK); // mod 32
        bitSet[wordNumber] |= (1 << bitNumber);
    }
    bool get(int i) {
        int wordNumber = (i >> SHIFT);
        int bitNumber = (i & MASK);
        return (bitSet[wordNumber] & (1 << bitNumber) != 0);
    }
    void clear(int i) {
        int wordNumber = (i >> SHIFT);
        int bitNumber = (i & MASK);
        bitSet[wordNumber] &= ~(1 << bitNumber);
    }
    int findUnsetBit() {
        for (int i = 0; i < size; i++) {
            for (int j =  0; j < BITSPERWORD; j++) {
                if (bitSet[i] & (1 << j) == 0) {
                    return (i*BITSPERWORD + j);
                }
            }
        }
    }
};