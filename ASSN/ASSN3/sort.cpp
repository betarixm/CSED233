#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


void swap(int& x, int& y){
    int z = x;
    x = y;
    y = z;
}

sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}


void sortAlg::bubbleSort(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    for (int i = 0; i < arr_size - 1; i++) {
        for(int j = arr_size - 1; j > i; j--){
            if(arr[j-1] > arr[j]) swap(arr[j-1], arr[j]);
        }
        printArray(fout); // DO NOT ERASE THIS LINE
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::insertionSort(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    for (int i = 1; i < arr_size; i++) {
        int target = arr[i];
        int j = 0;
        for(j = i - 1; j >= 0; j--){
            if(target < arr[j]){
                arr[j+1] = arr[j];
            } else {
                break;
            }
        }
        arr[j+1] = target;
        printArray(fout);// DO NOT ERASE THIS LINE
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}


void sortAlg::merge(int left, int mid, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int left_counter = left;
    int right_counter = mid + 1;
    int main_counter = 0;

    int size = right - left + 1;
    int* tmp = new int[size];

    while(main_counter < (right - left + 1)){
        int data;

        if(left_counter > mid){
            data = arr[right_counter++];
        } else if (right_counter > right){
            data = arr[left_counter++];
        } else {
            data = (arr[left_counter] < arr[right_counter])?(arr[left_counter++]):(arr[right_counter++]);
        }
        tmp[main_counter++] = data;
    }

    for(int i = 0; i < size; i++){
        arr[left + i] = tmp[i];
    }

    delete[] tmp;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::mergeSort(ofstream &fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(fout, left, mid);
        mergeSort(fout, mid + 1, right);
        merge(left, mid ,right);
        printArray(fout);// DO NOT ERASE THIS LINE
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}