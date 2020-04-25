#pragma once
#include <iostream>
#include <string>
using namespace std;

class MinHeap {

public:
    MinHeap();

    int heap_size;
    int *heap_arr;

    void minHeapProp(int);
    void insertKey(int);
    void deleteMin();
    string printHeap();

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add Private members if required ///////////
    void swap(int& a, int& b){
        int tmp = a;
        a = b, b = tmp;
    }

    int parentIdx(int idx){
        return ((idx - 1) / 2);
    }

    int leftChildIdx(int idx){
        return (idx*2)+1;
    }

    int rightChildIdx(int idx){
        return (idx*2)+2;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

};

