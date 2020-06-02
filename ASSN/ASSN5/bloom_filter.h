#pragma once
#include <iostream>
#include <string>
#include "hash_function.h"

using namespace std;


class BloomFilter {
public:
    BloomFilter(int key_size, int vector_size);
    ~BloomFilter();

    void print_vector(ostream &out);

    void insert(int key);
    string search(int key);

private:
    const int key_size;
    const int vector_size;
    bool* bit_vector;
    DivisionHashFunction* hf1;
    MidSquareHashFunction *hf2;
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

