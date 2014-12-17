//
//  bits.cpp
//  
//
//  Created by Janani Natarajan on 12/16/14.
//
//

#include iostream

using namespace std;

int setBitCount(int n)
{
    int count = 0;
    //naive
    while (n) {
        count += n & 1;
        n = n >> 1;
    }
    //alternate - the loop will run as many times as the no. of 1's
    while (n) {
        count++;
        n = n & (n-1);
    }
    return count;
}

int countNoOfBitsToConvert(int a, int b)
{
    //find the no. of bits that are different in 2 integers -- XOR
    return setBitCount(a ^ b);
}

int swapOddAndEvenBits(int x)
{
    // masking odd bits can be done with 10101010 (8bit) represented as 0xAA
    // once we find the no. of odd bits set, we can move to even positions
    // So bit mask for 32bit systems - 0xaaaaaaaa - (8 'a's to represent 32bits
    // each representing 4bits)
    // 0101010101 (8bit) - 0x55
    return ( ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1) );
}

bool isKthBitSet(int x, int i)
{
    int bitMask = 1 << i;
    return ((x & bitMask) != 0);
}

int getByte(int x, int n)
{
    // n << 3 tell us how much you need to shift n*8(bits)
    return (x >> (n << 3)) & 0xFF;
}

//swapping values
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))

bool compareSigns(int x, int y)
{
    return ((x ^ y) < 0); // true iff x and y have opposite signs
}

void PrintBinary(unsigned int d)
{
    for (unsigned int bit = 1u << (CHAR_BIT*sizeof(bit) -1); bit; bit >>= 1 ) {
         cout << (d & bit ? '1' : '0');
    }
    cout << endl;
}

int main()
{
    return 0;
}
