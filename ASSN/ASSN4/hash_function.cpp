#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int HashFunction::hashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    unsigned int target = pow(key, 2);
    unsigned int mask = genBitMask();
    unsigned int shift = key_size - index_size / 2;
    return (int)((target & mask) >> shift);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

int HashFunction::pow(int x, int r) {
    int result = x;
    while(--r) { result *= x; }
    return result;
}

unsigned int HashFunction::genBitMask() {
    unsigned int result = 0b0;
    int start = key_size - index_size / 2;
    int end = key_size + index_size / 2;
    for(int i = start; i < end; i++){
        result += pow(2, i);
    }
    return result;
}


///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
