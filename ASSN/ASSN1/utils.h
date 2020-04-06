#include <iostream>

using namespace std;

typedef struct Instruction {
    string command;
    int value;
} Instruction;

typedef struct InstructionSequence {
    Instruction* instructions;
    int length;
} InstructionSequence;

InstructionSequence* ParseInstructions(const char* arg);
void DeleteInstructionSequence(InstructionSequence* instr_seq);
void PrintInstructionSequence(InstructionSequence* instr_seq);

const char* const TASK_3_DEFAULT_ARGUMENT="[('append',1),('append',2),('insert_at',1)]";
const char* const TASK_4_DEFAULT_ARGUMENT="[('push',5),('push',3),('push',2)]";
const char* const TASK_5_DEFAULT_ARGUMENT="[('push',5),('push',3),('push',2)]";
const char* const TASK_6_DEFAULT_ARGUMENT="[('enqueue',5),('enqueue',3),('dequeue',NULL)]";
