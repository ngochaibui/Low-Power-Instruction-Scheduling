#ifndef _PROGRAM_H_
#define _PROGRAM_H_
struct BasicBlock{
       int start;
       int end;
};
//-----------------------------------------------------------
struct Program{
       int numOfIns;
       char ASMCode[1000][40];
       int leader[1000];  // mang danh dau cac leader
       char directive[3000];  // cac chi thi
       int numOfBBs;
       struct BasicBlock basicblock[100];
};
#endif
