#include "pisa.h"
#include <string.h>
void initPISA()
{
     instruction[0] = a0;
     instruction[1] = a1;
     instruction[2] = a2;
     instruction[3] = a3;
     instruction[4] = a4;
     instruction[5] = a5;
     instruction[6] = a6;
     instruction[7] = a7;
     instruction[8] = a8;
     instruction[9] = a9;
     instruction[10] = a10;
     instruction[11] = a11;
}
//tra ve so thu tu cua lenh
int indexOf(char* inst)
{
    char tmp[20];
    int length = strlen(inst);
    int i=0;
    while(i<length)
    {
        if(inst[i]=='\0' || inst[i]=='\t'||inst[i]==' ')
            break;
        tmp[i] = inst[i];
        i++;
    }
    tmp[i]='\0';
    for(i=0;i<isa_size;i++)
        if(strcmp(tmp,instruction[i])==0)
        {
            return i;
            break;
        }

    return -1;
}
