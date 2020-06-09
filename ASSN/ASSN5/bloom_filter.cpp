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
    this->bit_vector = new bool[this->vector_size];
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    for(int i = 0; i < vector_size; i++){
        bit_vector[i] = false;
    }

    hf1 = new DivisionHashFunction(vector_size);
    hf2 = new MidSquareHashFunction(key_size, vector_size);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

BloomFilter::~BloomFilter() {
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////

    /*             Write your codes if you need            */
    delete hf1;
    delete hf2;
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
    bit_vector[hf1->hashing(key)] = true;
    bit_vector[hf2->hashing(key)] = true;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string BloomFilter::search(int key) {
    /////////////////////////////////////////////////////////
    ///////////    TODO: Implement From Here    /////////////

    int hash1 = hf1->hashing(key);
    int hash2 = hf2->hashing(key);

    if(bit_vector[hash1] && bit_vector[hash2]){
        return "hit";
    } else {
        return "miss";
    }


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
