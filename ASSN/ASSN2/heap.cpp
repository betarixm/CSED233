#include "heap.h"
#include <iostream>
#include <string>

using namespace std;


MinHeap::MinHeap() {
    heap_size = 0;
    heap_arr = new int[100]; // Default array of size 100
}

string MinHeap::printHeap(){
    string answer;
    for (int i = 0; i < heap_size; i++)
        answer += to_string(heap_arr[i]) + " ";
    return answer;
}

void MinHeap::insertKey(int k) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    heap_arr[heap_size] = k;
    int parent = parentIdx(heap_size);
    int idx = heap_size++;
    for(;idx != 0; idx = parent, parent = parentIdx(idx)){
        if(heap_arr[parent] > heap_arr[idx]){
            swap(heap_arr[parent], heap_arr[idx]);
        } else {
            break;
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MinHeap::deleteMin() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if(heap_size == 0)
        return;
    heap_size--;
    swap(heap_arr[0], heap_arr[heap_size]);
    heap_arr[heap_size] = NULL;
    minHeapProp(0);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MinHeap::minHeapProp(int i) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if(i > heap_size) return;

    int lc = leftChildIdx(i);
    int rc = rightChildIdx(i);
    int minIdx = 0;

    if (lc >= heap_size){
        return;
    } else if (rc >= heap_size){
        minIdx = lc;
    } else {
        minIdx = (heap_arr[lc]<heap_arr[rc])?(lc):(rc);
    }

    if (heap_arr[minIdx] < heap_arr[i]){
        swap(heap_arr[minIdx], heap_arr[i]);
        minHeapProp(minIdx);
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}