/*
    Programming Assignment #3

*/
#include "utils.h"
#include "tree.h"
#include "bst.h"
#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


/*
    [Task 1] Quiz
    
    From given statements about the sorting algorithm, choose every wrong statement. 
    
    Statements
      (1) If the relative order of  elements with the same keys are retained after the sorting, it is a stable sort.
      (2) Bubble sort takes a more significant number of record swap than Selection sort.
      (3) The time complexity of Selection sort is O(n) in the best case.
      (4) Merge sort can be implemented in a non-recursive manner.
      (5) Merge sort is always faster than Insertion sort.
      (6) Bucket sort is a kind of non-comparison sort. O
      (7) For Quick sort, the choice of a pivot doesn’t affect the performance. X

    Print out your answer. 
    If you think there are multiple answers, 
    print out a sequence of answers in ascending order with the string separated with the spacebar. 
    If you believe every statement is correct, print out an empty string.
*/

void task_1(ofstream &fout) {
  fout << "[Task 1]" << endl;
  string answer = "2 3 5 7";  // TODO: Change to your answer
  fout << answer << endl;
}


/*
    [Task 2] bubble sort

    Description:
        Implement a function that sorts a given array using the bubble sort algorithm in ascending order.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::bubbleSort function

    Input:
        ('insert',integer): insert integer into the array
        ('bubbleSort',NULL): sort the array using bubble sort algorithm

    Output:
        Every value in the array for each sorting step including the initial step,
        string separated with the white space (please use built-in function to print the array).
        You don’t need to consider exceptional cases such as overflow or an empty array.
        We will not test such cases.

*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 2]" << endl;
    try {
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0) {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            } else if (command.compare("bubbleSort") == 0) {
                sort.printArray(fout);
                sort.bubbleSort(fout);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 3] insertion sort

    Description:
        Implement a function that sorts a given array using the insertion sort algorithm in ascending order.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::insertionSort function

    Input:
        ('insert',integer): insert integer into the array
        ('insertionSort',NULL): sort the array using insertion sort algorithm

    Output:
        Every value in the array for each sorting step including the initial step,
        string separated with the white space (please use built-in function to print the array).
        You don’t need to consider exceptional cases such as overflow or an empty array.
        We will not test such cases.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
    try {
        sortAlg sort;

        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0) {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            } else if (command.compare("insertionSort") == 0) {
                sort.printArray(fout);
                sort.insertionSort(fout);
            } else {
                cerr << "Invalid command:" << command << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 4] merge sort

    Description:
        Implement a function that sorts a given array using the merge sort
        algorithm in ascending order using recursive merge sort.
        Split a list of elements into two sublists with the first sublist bigger than the second sublist,
        for a case when the input array has an odd number of elements.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::mergeSort function
        TODO: Implement sortAlg::merge function

    Input:
        ('insert',integer): insert integer into the array
        ('mergeSort',NULL): sort the array using merge sort algorithm

    Output:
        Every value in the array for each sorting step including the initial step,
        string separated with the white space (please use built-in function to print the array).
        You don’t need to consider exceptional cases such as overflow or an empty array.
        We will not test such cases.
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 4]" << endl;
    try {
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0) {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            } else if (command.compare("mergeSort") == 0) {
                sort.printArray(fout);
                sort.mergeSort(fout, 0, sort.arr_size - 1);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 5] BST insertion

    Description:
        Implement a function that inserts an element into a BST.
        You can modify bst.cpp and bst.h files for this problem.

        TODO: Implementation BinearySearchTree:insert function

    Input of BinearySearchTree:insert:
        Key of the element to be inserted.

    Output of BinearySearchTree:insert:
        Return 1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    task_5 prints
        the return for *each* insertion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
    try {
        BinarySearchTree tree;
        bool ret;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                ret = tree.insert(key);
                fout << ret << endl;
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << tree.preOrder() << endl;
        fout << tree.inOrder() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 6] BST deletion

    Description:
        Implement a function that deletes an element from a BST.
        You can modify bst.cpp and bst.h files for this problem.

        TODO: Implementation BinearySearchTree:erase function

    Input of BinearySearchTree:erase:
        Key of the element to be deleted.

    Output of BinearySearchTree:erase:
        Return 1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not delete any element)

    task_6 prints
        the return for *each* insertion/deletion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 6]" << endl;
    try {
        BinarySearchTree tree;
        bool ret;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                ret = tree.insert(key);
                fout << ret << endl;
            } else if (command.compare("delete") == 0) {
                ret = tree.erase(key);
                fout << ret << endl;
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << tree.preOrder() << endl;
        fout << tree.inOrder() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence instr_seq;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3) {
        try {
            instr_seq.parseInstructions(argv[2]);
        }
        catch (const char *e) {
            cerr << e << endl;
            return -1;
        }
    }

    // Running the task(s)
    switch (task_num) {
        case 1:
            task_1(fout);
            break;
        case 2:
            task_2(fout, instr_seq);
            break;
        case 3:
            task_3(fout, instr_seq);
            break;
        case 4:
            task_4(fout, instr_seq);
            break;
        case 5:
            task_5(fout, instr_seq);
            break;
        case 6:
            task_6(fout, instr_seq);
            break;
        case 0:
            task_1(fout);

            instr_seq.parseInstructions(TASK_2_DEFAULT_ARGUMENT);
            task_2(fout, instr_seq);

            instr_seq.parseInstructions(TASK_3_DEFAULT_ARGUMENT);
            task_3(fout, instr_seq);

            instr_seq.parseInstructions(TASK_4_DEFAULT_ARGUMENT);
            task_4(fout, instr_seq);

            instr_seq.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq);

            instr_seq.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq);
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
