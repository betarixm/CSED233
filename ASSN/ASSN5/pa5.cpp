/*
    Programming Assignment #5
*/
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include "graph.h"
#include "hash_function.h"
#include "hash_table.h"
#include "bloom_filter.h"
#include "utils.h"

using namespace std;


/*
    [Task 1] Quiz
    (1) What is the appropriate data structure for Depth First Search algorithm?
        1. Stack
        2. Queue
        3. Priority queue
        4. None of above

    (2) Choose a sequence that can be obtained from Depth First Search traversal given the graph below.
        The search starts at vertex ‘0’ and follows the ascending order.
        1. 0 1 2 4 3 5
        2. 0 1 2 5 4 3
        3. 0 1 2 4 5 3
        4. 0 1 2 3 4 5

    (3) Which vertices are strongly connected to the vertex ‘6’ in the given graph?
        1. 0, 1, 3, 4, 7
        2. 0, 1, 2, 3, 4, 5
        3. 0, 1, 2, 4, 5
        4. 0, 1, 5, 7

    (4) Choose a sequence that corresponds to the Breadth First Search traversal for a graph below.
        The search starts at vertex 0 and follows lexicographic ordering.
        1. 0 1 2 4 3 5
        2. 0 1 2 5 4 3
        3. 0 1 2 4 5 3
        4. 0 1 2 3 4 5

    Print out a sequence of answers of each sub-quiz with the string separated with the spacebar.
    Each sub-quiz will have 1 correct answer. If you think the answers of
    the quiz 1-(1), 1-(2), 1-(3) and 1-(4) are 1, 1, 1, 1 respectively, then print 1 1 1 1.

*/

void task_1(ofstream &fout) {
    fout << "[Task 1]" << endl;
    string answer = "1 1 1 1";  // TODO: Change to your answer
    fout << answer << endl;
}


/*
    [Task 2] Connected Components of Graph 

    Description:
        Implement a function that retrieves the largest connected components from the given undirected graph. 
        This function finds the largest connected component that can be found in the given graph and prints out the node labels of it. 
        There might be multiple connected components with the same l_size.
        If that is the case, retrieve the component that comes first in lexicographical order. 
        For instance, if two connected components, (A, B, C) and (A, B, D) are found, select
        (A, B, C) because C comes first than D in lexicographical order. 
        You can modify graph.cpp and graph.h files for this problem.
    
        TODO: Implement Graph::addEdge and Graph::getConnectedComponent functions

    Input & Output:
        Input: Pairs of node labels that indicate edges.
        Output: A sequence of the node labels of the largest connected component. 
                It should be sorted in lexicographical order and separated with space. 
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 2]" << endl;
    try {
      Graph graph;
      for (int i = 0; i < instr_seq.getLength(); i++) {
          string firstNode = instr_seq.getInstruction(i).getCommand();
          string secondNode = instr_seq.getInstruction(i).getValueStr();
          graph.addEdge(firstNode, secondNode);
      }
      fout << graph.getConnectedComponent() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 3] Cyclic / Acyclic Graph

    Description:
        Implement a function that returns the number of cycles in the given directed graph. 
        A cycle is a non-empty path in which the only repeated vertices are the first and last vertices. 
        Unlike task 2, the edges of the graph have direction in this time. 
        For instance, (‘A’,’B’) is different from (‘B’,’A’). 
        This function should return 1 if the given directed graph has at least one cycle, or 0 otherwise.
        You can modify graph.cpp and graph.h files for this problem.
        
        TODO: Implement Graph::getCycleCount function
    
    Input & Output:
        Input: Pairs of node labels that indicate edges. 
          - (A, B): a edge from node A to node B.
          - If the input edge already exist in the graph, ignores the input.
        Output: The number of cycles in the given directed graph.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
    try {
      Graph graph;
      for (int i = 0; i < instr_seq.getLength(); i++) {
          string firstNode = instr_seq.getInstruction(i).getCommand();
          string secondNode = instr_seq.getInstruction(i).getValueStr();
          graph.addEdge(firstNode, secondNode);
      }
      fout << graph.getCycleCount() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 4] Open hashing

    Description:
        Implement a hash table with open hashing to handle collision (a.k.a separate chaining).
        This hash table uses a key obtained from the string folding method \
            (please check page 6 in Week10_02_Dictionary_Hashing.pdf).
        The l_size of the hash table is M.
        You can modify hash_function.cpp, hash_function.h, hash_table.cpp, \
            and hash_table.h files for this problem.

        TODO: Implementation HashTable::insert, HashTable::search, \
                and HashTable::print_table functions

    Input & Output:
        Input: A sequence of commands
          - ('M', integer): The l_size of an idex. (The first command is always 'M')
          - ('insert', 'string'): insert string into the hash table.
          - ('search', 'string'): search string in the hash table.
        Output
          - Print out "hit" or "miss" for each search command
          - Print out the list of the values for each slot of the hash table
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 4]" << endl;
    try {
        int M;
        StringFoldingHashFunction *hf;
        HashTable *ht;

        if (instr_seq.getLength() < 1 ||
            instr_seq.getInstruction(0).getCommand().compare("M") != 0) {
            cerr << "Invalid command" << endl;
            exit(-1);
        }

        M = instr_seq.getInstruction(0).getValue();
        hf = new StringFoldingHashFunction(M);
        ht = new HashTable(M, hf);

        for (int i = 1; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            string value = instr_seq.getInstruction(i).getValueStr();
            if (command.compare("insert") == 0) {
                ht->insert(value);
            } else if (command.compare("search") == 0) {
                fout << ht->search(value) << endl;
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

/*
    [Task 5] Bloom filter

    Description:
        Implement a bloom filter
        Please read the document (ProgrammingAssignment#5.pdf) for the details.

        TODO: Implementation HashTable::lookup_bloom_filter, BloomFilter::insert, \
                and BloomFilter::search functions

    Input & Output:
        Input: A sequence of commands
          - ('M', integer): The l_size of an idex. (The first command is always 'M')
          - ('b', integer): the l_size of a bloom filter. (The second command is always 'b')
          - ('insert', 'string'): insert string into the hash table.
          - ('search', 'string'): search string in the hash table.
        Output
          - For each search command, print out "hit" or "miss" of the bloom filter.
            If the filter is "miss", print out "hit" or "miss" of the hash table.
          - Print out the bits of the bloom filter.
          - Print out the list of the values for each slot of the hash table.
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
    try {
        int key_size = 16;
        int M, b;
        StringFoldingHashFunction *hf;
        BloomFilter *bloom_filter;
        HashTable *ht;

        if (instr_seq.getLength() < 2 ||
            instr_seq.getInstruction(0).getCommand().compare("M") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("b") != 0) {
            cerr << "Invalid command" << endl;
            exit(-1);
        }

        M = instr_seq.getInstruction(0).getValue();
        b = instr_seq.getInstruction(1).getValue();
        hf = new StringFoldingHashFunction(M);
        bloom_filter = new BloomFilter(key_size, b);
        ht = new HashTable(M, hf, bloom_filter);

        for (int i = 2; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            string value = instr_seq.getInstruction(i).getValueStr();
            string lookup;
            if (command.compare("insert") == 0) {
                ht->insert(value);
            } else if (command.compare("search") == 0) {
                lookup = ht->lookup_bloom_filter(value);
                fout << "Bloom: " << lookup;
                if (lookup.compare("hit") == 0)
                    fout << ", HashTable: " << ht->search(value);
				fout << endl;
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }   
        }   

        bloom_filter->print_vector(fout);
        ht->print_table(fout);

        delete ht;
        delete bloom_filter;
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

            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
