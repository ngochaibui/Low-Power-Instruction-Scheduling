#include <stdio.h>
#include"Scheduling.h"
#include "Program.h"
#include "BasicBlockPartition.h"
//#include "List.h"  //khong can include vi trong DFG.h da include roi
#include "DFG.h"
#include "Genetic.h"
#include "reduceMemAccess.h"
//#include "pisa.h"

int main()
{
    struct Program program;

    int i,j;
    //*
    //inputProgram("../samplebench/perm.s",&program);
    inputProgram("asm4.s",&program);
    BBpartition(&program);
    outBBToFile("BBAsm.txt",program);
    printf("numOfBBs: %d \n",program.numOfBBs);
    struct DFG dfg[program.numOfBBs];
    //struct SCG scg[program.numOfBBs];
    inputPDT();
    initPISA();
    /*
    checkRegistersInUse(&program);
    for(i=0;i<program.numOfBBs;i++)
        if(program.basicblock[i].start < program.basicblock[i].end)
        {
            //checkRegistersInUse(&program,i);
            //reduceMEMAccess(&program,i);
        }
    reduceMEMAccess(&program); //*/

    ///*
    for(i=0;i<program.numOfBBs;i++)
        if(program.basicblock[i].start < program.basicblock[i].end)
        {
            constructDFG(program,i,&dfg[i]);
            dfg[i].program = &program;
            //ASAP2(&dfg[i]);
            //ALAP2(&dfg[i]);
        }
    outDFGToFile("dfg.txt",dfg[0]);
    //for(i=0;i<dfg[0].numOfNode;i++)
    //   printf("%d  %d \n",dfg[0].node[i].ASAP_value,dfg[0].node[i].ALAP_value); //*/
    //*
    for(i=0;i<program.numOfBBs;i++)
        if(program.basicblock[i].start < program.basicblock[i].end)
        {
            Genetic_Schedule(&dfg[i]);
            //ListSchedule2(&dfg[i]);
            //schedule2(&dfg[i]);
            //ASAP2(&dfg[i]);
            //for(j=0;j<10;j++)
            //    improveScheduling(&dfg[i]);
        }
    printf("\nscheduled: \n");
    for(i=0;i<dfg[0].numOfNode;i++)
       printf("%d  \n",dfg[0].schedule[i]);
    outProgramScheduledToFile("asm4sc.s",program,dfg);
    //outProgramScheduledToFile("../test20/perms2.s",program,dfg);//*/
    //outProgramToFile("../test19/heaprd2.s",program); //*/
    return 0;
}
