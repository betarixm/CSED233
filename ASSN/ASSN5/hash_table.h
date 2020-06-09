#pragma once
#include <iostream>
#include <string>
#include "hash_function.h"
#include "bloom_filter.h"
#include "graph.h" // By QnA, I can include this. https://lms.postech.ac.kr/Board.do?cmd=viewBoardContents&boardInfoDTO.boardInfoId=20200900140073401661225QN&boardContentsDTO.boardContentsId=BOAD_200604191826c0f103eb&boardContentsDTO.contentsNo=107&boardContentsDTO.gongjiYn=N&gubun=V&curPage=2&typeYn=Y
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
    List<string>* table;

    int sumStr(string& value);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

