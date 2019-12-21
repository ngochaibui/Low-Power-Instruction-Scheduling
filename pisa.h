#ifndef _PISA_H_
#define _PISA_H_
int isa_size = 12;
char* instruction[12];

char a0[] = "addu";
char a1[] = "subu";
char a2[] = "lw";
char a3[] = "sw";
char a4[] = "sll";
char a5[] = "slt";
char a6[] = "sra";
char a7[] = "mflo";
char a8[] = "move";
char a9[] = "li";
char a10[] = "la";
char a11[] = "mult";
// cha hieu sao neu bo cac lenh gan instruction[i] ra khoi ham, thi loi~
void initPISA();
//tra ve so thu tu cua lenh
int indexOf(char* inst);
#endif
