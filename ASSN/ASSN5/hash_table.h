#pragma once
#include <iostream>
#include <string>
#include "hash_function.h"
#include "bloom_filter.h"

using namespace std;


class HashTable {
public:
    HashTable(int table_size, StringFoldingHashFunction *hf);
    HashTable(int table_size, StringFoldingHashFunction *hf, BloomFilter *bloom_filter);
    ~HashTable();

    void print_table(ostream &out);

    void insert(string value);
    string search(string value);

    string lookup_bloom_filter(string value);

private:
    const int table_size;
    StringFoldingHashFunction *hf;
    BloomFilter *bloom_filter;
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

