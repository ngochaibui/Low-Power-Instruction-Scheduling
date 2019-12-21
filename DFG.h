#ifndef _DFG_H_
#define _DFG_H_
#include "List.h"
#define MAX_NODES 60
//-----------------------------------------------
struct Node{
       int ins_index;
       int ASAP_value;
       int ALAP_value;
       int assigned_value;
       struct List pred;
       struct List succ;
};
//-----------------------------------------------
struct DFG{
     struct Program* program;  // con tro tham chieu den 1 Program
     int BB_index;             // chi so cua basic block
     int numOfNode;
     int schedule[MAX_NODES];
     struct Node node[MAX_NODES];  // mang luu cac node
};
//-----------------------------------------------
void initNode(struct Node* node);
//char read[2][10];
void ReadFrom(struct Program program, int ins_index);
//char write[10];
char* WriteTo(struct Program program, int ins_index);
void constructDFG(struct Program program, int BB_index, struct DFG *dfg);
void outDFGToFile(char* filename, struct DFG dfg);
char read[2][10];
char write[10];
#endif
