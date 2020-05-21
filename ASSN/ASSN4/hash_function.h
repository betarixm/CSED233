#pragma once
#include <iostream>
#include <string>
using namespace std;

class HashFunction {

public:
    HashFunction(int n, int r) : key_size(n), index_size(r) { };

    int hashing(int key);

private:
    int key_size;
    int index_size;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    unsigned int genBitMask(){
        unsigned int result = 0b0;
        int start = key_size - index_size / 2;
        int end = key_size + index_size / 2;
        for(int i = start; i < end; i++){
            result += pow(2, i);
        }
        return result;
    }

    int pow(int x, int r){
        int result = x;
        while(--r) { result *= x; }
        return result;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

