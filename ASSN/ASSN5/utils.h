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

const char* const TASK_2_DEFAULT_ARGUMENT="[('A','B'), ('C','D'), ('C','E')]";
const char* const TASK_3_DEFAULT_ARGUMENT="[('A','B'), ('A','C'), ('C','D'), ('C','E'), ('D','B'), ('D','E')]";
const char* const TASK_4_DEFAULT_ARGUMENT="[('M', 4), ('insert', 'apple'), ('insert', 'book'), ('insert', 'car'), ('search', 'apple')]";
const char* const TASK_5_DEFAULT_ARGUMENT="[('M', 4), ('b', 16), ('insert', 'apple'), ('insert', 'book'), ('insert', 'car'), ('search', 'apple')]";

