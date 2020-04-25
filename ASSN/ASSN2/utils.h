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


const char* const TASK_2_DEFAULT_ARGUMENT="4(2(3)(1))(6(5))";
const char* const TASK_2_DEFAULT_ARGUMENT_2="preorder";
const char* const TASK_3_DEFAULT_ARGUMENT="4(2(3)(1))(6(5))";
const char* const TASK_4_DEFAULT_ARGUMENT="4(2(3)(1))(6(5))";
const char* const TASK_5_DEFAULT_ARGUMENT="[('insert',28),('insert',9),('insert',27),('insert',10),('insert',3),('insert',45)]";
const char* const TASK_6_DEFAULT_ARGUMENT="[('insert',28),('insert',9),('insert',27),('insert',10),('insert',3),('insert',45),('delMin',NULL)]";

