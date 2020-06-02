#include <iostream>
#include <fstream>
#include <string>
#include "hash_function.h"
#include "bloom_filter.h"

using namespace std;


BloomFilter::BloomFilter(int key_size,
                         int vector_size)
:    key_size(key_size), vector_size(vector_size)
{
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////

    this->bit_vector = new bool[this->vector_size];  // Do not modify this line

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

BloomFilter::~BloomFilter() {
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    delete[] this->bit_vector;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BloomFilter::print_vector(ostream &out) {
    for (int i=0; i < this->vector_size; i++) {
        out << this->bit_vector[i];
    }
    out << endl;
}

void BloomFilter::insert(int key) {
    /////////////////////////////////////////////////////////
    ///////////   TODO: Implement From Here     /////////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string BloomFilter::search(int key) {
    /////////////////////////////////////////////////////////
    ///////////    TODO: Implement From Here    /////////////

    return "miss";

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
