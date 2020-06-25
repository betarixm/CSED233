#include <iostream>

using namespace std;

class Instruction {
public:
    void setCommand(string cmd);
    void setValue(int val);
    void setValueStr(string val);

    string getCommand();
    int getValue();
    string getValueStr();

private:
    string command;
    string value_str;
    int value;
};

class InstructionSequence {
public:
    InstructionSequence();
    ~InstructionSequence();

    int getLength();
    Instruction& getInstruction(int index);

    void parseInstructions(const char* arg);
    void printInstructions();

private:
    Instruction* instructions;
    int length;
};

const char* const TASK_1_DEFAULT_ARGUMENT="[('0','2'), ('0','1'), ('0','3'), ('1','2'), ('1','3'), ('1','4'), ('1','5'), ('2','5'), ('2','4')]";
const char* const TASK_2_DEFAULT_ARGUMENT="[('0','1'), ('0','2'), ('1','5'), ('5','4'), ('2','4'), ('2','3')]";
const char* const TASK_3_DEFAULT_ARGUMENT="[('A-B',10),('A-C',3),('B-D',5),('C-B',2),('C-E',15),('A-D',20),('D-E',11),('A','E')]";
const char* const TASK_4_DEFAULT_ARGUMENT="[('A-B',4),('A-F',3),('B-F',6),('B-C',9),('F-E',-2),('E-F',5),('C-E',-3),('E-C',8),('E-D',6)]";
const char* const TASK_5_DEFAULT_ARGUMENT="[('A-B', 3), ('A-C', 1), ('B-C', 4), ('B-D', 1), ('C-D', 2), ('D-E', 5), ('MST', 'A')]";
const char* const TASK_6_DEFAULT_ARGUMENT="[('A-B', 3), ('A-C', 1), ('B-C', 4), ('B-D', 1), ('C-D', 2), ('D-E', 5), ('MST', NULL)]";
