#pragma once
#include <iostream>
#include <string>

using namespace std;


class DivisionHashFunction {
public:
    DivisionHashFunction(int table_size) : table_size(table_size) { };
    int hashing(int key);

private:
    const int table_size;
};

class MidSquareHashFunction {
public:
    MidSquareHashFunction(int key_size, int table_size);
    int hashing(int key);

private:
    const int key_size;
    const int table_size;
    int index_size;
    int skip_bits;
};

class StringFoldingHashFunction {
public:
    StringFoldingHashFunction(int table_size) : table_size(table_size) { };
    int hashing(string value);

private:
    const int table_size;
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
