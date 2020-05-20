#include <iostream>

using namespace std;

class Instruction {
public:
    void setCommand(string cmd);
    void setValue(int val);

    string getCommand();
    int getValue();

private:
    string command;
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

const char* const TASK_3_DEFAULT_ARGUMENT="[('insert',4), ('insert',2), ('insert',10), ('insert',9), ('insert',15), ('insert',5)]";
const char* const TASK_4_DEFAULT_ARGUMENT="[('insert',4), ('insert',2), ('insert',10), ('insert',9), ('insert',15), ('insert',5), ('insert',0), ('delete',4), ('insert',10)]";
const char* const TASK_5_DEFAULT_ARGUMENT="[('n', 4), ('r', 4), ('key', 10)]";
const char* const TASK_6_DEFAULT_ARGUMENT="[('n', 4), ('r', 2), ('insert', 15), ('insert', 2), ('insert', 3)]";

