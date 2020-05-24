#pragma once
#include <iostream>
#include <string>
#include "hash_function.h"

using namespace std;


enum TableState {
    EMPTY,
    OCCUPIED,
    DELETED,
};


class HashTable {
public:
    HashTable(int table_size, HashFunction *hf);
    ~HashTable();

    void print_table(ostream &out);

    void insert(int key);
    void erase(int key);

private:
    const int table_size;
    HashFunction *hf;
    int *table;
    TableState *states;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    bool isDuplicated(int key){
        for(int i = 0; i < table_size; i++){
            if(key == table[i]){
                return true;
            }
        }
        return false;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

