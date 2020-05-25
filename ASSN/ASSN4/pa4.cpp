/*
    Programming Assignment #4
*/
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include "tree.h"
#include "avl.h"
#include "hash_function.h"
#include "hash_table.h"
#include "utils.h"

using namespace std;


/*
    [Task 1] Quiz

    From given statements about the 2-3-4 tree, print T (true) or F (false) for each statement.
    You will get credit when all the answers are correct.

    Statements
        (1) Each internal node can have only 2 or 4 children.
        (2) Every node can hold only 2 or 3 or 4 data elements.
        (3) All keys in the left subtree are smaller than the first key in the parent node.
        (4) All keys in the right subtree are greater than the second key in the parent node.
        (5) A 2-3-4 tree is a B-tree of order 4.
        (6) 2-3-4 trees aim to have the largest tree height possible.

    Print out a sequence of answers of each statement with the string separated with the spacebar.
    The answer is either T (true) or F (false). If you think the answers of the statements
    (1)~(3) are true and those of (4)~(6) are false then print "T T T F F F".

*/

void task_1(ofstream &fout) {
    fout << "[Task 1]" << endl;
    string answer = "F F T T T F";  // TODO: Change to your answer
    fout << answer << endl;
}


/*
    [Task 2] Quiz

    Print out the answer of each sub-quiz in quiz order.
    You will get credit when all the answers of the sub quizzes are correct.

    (1) B-tree of order n is a n-way tree in which each non-root node contains ______.
        1. at most (n – 1)/2 keys
        2. exact (n – 1)/2 keys
        3. at least 2n keys
        4. at least (n – 1)/2 keys

    (2) B-tree is a tree data structure that can keep data sorted and allow searches, insertions, and deletions in ______ time.
        1. O(1)
        2. O(log n)
        3. O(n)
        4. O(2^n)

    (3) A B-tree of order 4 and of height 3 will have a maximum of _______ leaves.
        1. 64
        2. 81
        3. 255
        4. 256

    Print out a sequence of answers of each sub-quiz with the string separated with the spacebar.
    Each sub-quiz will have 1 correct answer. If you think the answers of the
    quiz 2-(1), 2-(2) and 2-(3) are 1, 4, 3, respectively, then print 1 4 3.

*/

void task_2(ofstream &fout) {
    fout << "[Task 2]" << endl;
    string answer = "4 2 3";  // TODO: Change to your answer
    fout << answer << endl;
}


/*
    [Task 3] AVL Tree Insertion

    Description:
        Implement a function that inserts an element into an AVL tree. 
        The insertion might cause the AVL tree to violate its properties (imbalances).  
        Your code should be able to resolve the imbalances of the AVL tree (LL, RR, LR, RL). 
        You can modify avl.cpp and avl.h files for this problem

        TODO: Implementation AVLTree::insert function


    Input of AVLTree::insert function
        Key of the element to be inserted

    Output of AVLTree::insert function
        0, if the insertion is successful.
        1, if the key already exists in the tree.
    
    task_3 prints
        The return value for each insertion and
        The results of preorder and inorder traversal of the constructed tree.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
    try {
        AVLTree tree;
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
    [Task 4] AVL Tree Deletion

    Description:
        Implement a function that deletes an element from an AVL tree. 
        Same with the previous task, your code should be able to resolve the imbalances after the deletion. 
        You can modify avl.cpp and avl.h files for this problem

        TODO: Implementation AVLTree::erase function


    Input of AVLTree::erase function
        Key of the element to be inserted or deleted

    Output if AVLTree::erase function
        0, if the deletion is successful.
        1, if the key does not exist in the tree.
    
    task_4 prints
        The return value for each insertion & deletion and
        The results of preorder and inorder traversal of the constructed tree.
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 4]" << endl;
    try {
        AVLTree tree;
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

/*
    [Task 5] Mid-square hashing

    Description:
        Implement a mid-square hash function
        This hash function is used with n-bit integer keys \
          and hashing into a table of size 2^r, when r is even
        You can modify hash_function.cpp and hash_function.h files

        TODO: Implementation HashFunction::hashing function


    Input: Three commands (The order is always 'n', 'r', and 'key')
      - ('n', integer): The size of a key
      - ('r', integer): The size of an index
      - ('key', integer): A key to be hashed (in decimal)

    Output
      - The result (i.e. index) of hashing in decimal
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
    try {
        int n, r, key;
        int idx;
        HashFunction *hf;

        if (instr_seq.getLength() != 3 ||
            instr_seq.getInstruction(0).getCommand().compare("n") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("r") != 0 ||
            instr_seq.getInstruction(2).getCommand().compare("key") != 0) {
            cerr << "Invalid command" << endl;
            exit(-1);
        }

        n = instr_seq.getInstruction(0).getValue();
        r = instr_seq.getInstruction(1).getValue();
        key = instr_seq.getInstruction(2).getValue();
        hf = new HashFunction(n, r);

        idx = hf->hashing(key);

        fout << idx << endl;

        delete hf;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 6] Hash table

    Description:
        Implement a closed hash table with rehashing implementation.
        This hash table is used with n-bit integer keys \
          and hashing into a table of size 2^r, when r is even
        This hash table uses linear probing as a collision handling method.
        The index of the key k after i-th collision, h_i(k), is:
            h_i(k) = h(k) + i
        when h is the hash function implemented in task_5.
        You can modify hash_table.cpp and hash_table.h files for this problem.

        TODO: Implementation HashTable::insert & HashTable::erase functions


    Input: A sequence of commands
      - ('n', integer): The size of a key
                        (The first command is always 'n')
      - ('r', integer): The size of an index
                        (The second command is always 'r')
      - ('insert', integer): Insert integer into the hash table
      - ('delete', integer): Delete integer from the hash table

    Output: For each slot of the hash table, print out
      - the value if the state of the slot is occupied
      - the state if the state of the slot is empty or deleted
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 6]" << endl;
    try {
        int n, r, key;
        HashFunction *hf;
        HashTable *ht;

        if (instr_seq.getLength() < 2 ||
            instr_seq.getInstruction(0).getCommand().compare("n") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("r") != 0) {
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        n = instr_seq.getInstruction(0).getValue();
        r = instr_seq.getInstruction(1).getValue();
        hf = new HashFunction(n, r);
        ht = new HashTable(pow(2, r), hf);

        for (int i = 2; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                ht->insert(key);
            } else if (command.compare("delete") == 0) {
                ht->erase(key);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }

        ht->print_table(fout);

        delete ht;
        delete hf;
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
        } catch (const char *e) {
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
            task_2(fout);
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

            task_2(fout);

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
