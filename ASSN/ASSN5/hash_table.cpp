#include <iostream>
#include <fstream>
#include <string>
#include "hash_function.h"
#include "hash_table.h"

using namespace std;


HashTable::HashTable(int table_size,
                     StringFoldingHashFunction *hf)
:    table_size(table_size)
{
    this->bloom_filter = nullptr;
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////

    /*             Write your codes if you need            */

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

HashTable::HashTable(int table_size,
                     StringFoldingHashFunction *hf,
                     BloomFilter *bloom_filter)
:    table_size(table_size)
{
    this->bloom_filter = bloom_filter;
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////

    /*             Write your codes if you need            */

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

HashTable::~HashTable() {
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string HashTable::lookup_bloom_filter(string value) {
    int key;
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    return this->bloom_filter->search(key);
}

void HashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": [";
        /////////////////////////////////////////////////////
        /////////   TODO: Implement From Here     ///////////

        /////////      End of Implementation      ///////////
        /////////////////////////////////////////////////////
        out << "]" << endl;
    }
}

void HashTable::insert(string value) {
    int key;
    /////////////////////////////////////////////////////////
    ///////////   TODO: Implement From Here     /////////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    if (this->bloom_filter != nullptr)
        this->bloom_filter->insert(key);
}

string HashTable::search(string value) {
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
