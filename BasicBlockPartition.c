#include <stdio.h>
#include <string.h>
#include "BasicBlockPartition.h"
#include "DFG.h"
#include "Program.h"

//--------------------------------------------------------------
void inputProgram(char* sourceFile, struct Program *program)
{
     FILE *input;
     input = fopen(sourceFile,"r");
     int i,j;
     int ignore;
     char c;
     program->numOfIns =0;
     i=0;
    while(c!=EOF){
             c=fgetc(input);
             program->directive[i]=c;
             i++;
             if(i>5)
                if(program->directive[i-5]=='.' && program->directive[i-4]=='e' && program->directive[i-3]=='n'
                 && program->directive[i-2]=='t' && (program->directive[i-1]==' '||program->directive[i-1]=='\t' ))
                 break;
     }
     c=fgetc(input);
     while(c!='\n')
     {
             program->directive[i]=c;
             i++;
             c=fgetc(input);
     }
     program->directive[i]='\0';
     i=0;
     while(c != EOF){
           //program->ASMCode[i] = (char*)malloc(30);
           ignore = 0;
           j=0;
           while ( ( c = fgetc( input ) ) != '\n' && ( c != EOF))
           {
                   if(c=='#') ignore=1;
                   //if(j==0 && (c!=' '||c!='\t'))
                   if(ignore==0 && c!=13 &&!(j==0 && c =='\t')){
                         program->ASMCode[i][j]=c;
                          j++;
                   }
           }
           while(program->ASMCode[i][j-1]==' '||program->ASMCode[i][j-1]=='\t')
                j--;
           program->ASMCode[i][j]= '\0';
           if(strcmp(program->ASMCode[i],"")!=0 && strcmp(program->ASMCode[i]," ")!=0 && strcmp(program->ASMCode[i],"\t")!=0)
           {
                program->numOfIns++;
                i++;
           }
     }
     fclose(input);
}
//-----------------------------------------------
int isJump(char* instruction)
{
    if(strlen(instruction)>2 && instruction[0]=='j' && (instruction[1]==' '||instruction[1]=='\t'))
        return 1;
    else if(strlen(instruction)>4 && instruction[0]=='j' && instruction[1]=='a' && instruction[2]=='l'
            && (instruction[3]==' '||instruction[3]=='\t'))
         return 2;
    else if(strlen(instruction)>4 && instruction[0]=='b' && instruction[1]=='e' && instruction[2]=='q'
            && (instruction[3]==' '||instruction[3]=='\t'))
         return 3;
    else if(strlen(instruction)>4 && instruction[0]=='b' && instruction[1]=='n' && instruction[2]=='e'
            && (instruction[3]==' '||instruction[3]=='\t'))
         return 4;
    else
        return 0;
}
//-----------------------------------------------
// lay nhan~ nhay den
char label[30];
char* getLabel(char* jumpIns)
{
    int i=0,j=0, comma=0; // so dau phay
    int jumpType = isJump(jumpIns);

    if(jumpType==1 || jumpType==2)
    {
        while(i<strlen(jumpIns))
        {
            if((jumpIns[i]==' '||jumpIns[i]=='\t') && i>0)
                break;
            else i++;
        }
    }
    else if(jumpType==3 || jumpType==4)
    {
        while(i<strlen(jumpIns))
        {
            if(jumpIns[i]==',')
            {
                if(comma == 1)
                    break;
                else {
                    i++;
                    comma++;
                }
            }
            else i++;
        }
    }
    i++;
    while(i<strlen(jumpIns) && jumpIns[i]!=' '&& jumpIns[i]!='\t' && jumpIns[i]!='\n')
    {
        label[j] = jumpIns[i];
        i++;
        j++;
    }
    label[j]=':';
    j++;
    label[j]='\0';
    return label;
}
//-----------------------------------------------
void BBpartition(struct Program *program)
{
     int i,j,k;
     //program->leader = (int*)malloc(program->numOfIns);
     program->numOfBBs = 1;
     program->leader[0] = 1;

     for(i=1; i< program->numOfIns; i++)
            program->leader[i] = 0;
     for(i=0; i< program->numOfIns; i++)
     {
            if(isJump(program->ASMCode[i])>0 || strcmp(program->ASMCode[i],"nop")==0
               || (i<program->numOfIns-1 && program->ASMCode[i+1][strlen(program->ASMCode[i+1])-1]==':'))
            {
                  if(i<program->numOfIns-1 && program->leader[i+1] == 0)
                  {
                        program->leader[i+1] = 1;
                        program->numOfBBs++;
                  }
                  char* label = getLabel(program->ASMCode[i]);  //lay' nhan~ nhay? den'
                  for(k=0; k< program->numOfIns; k++)
                        if(strcmp(program->ASMCode[k],label)==0 && program->leader[k] ==0 )
                        {
                             program->leader[k] = 1;
                             program->numOfBBs++;
                        }
            }
     }
     //program->basicblock = (struct BasicBlock*)malloc(program->numOfBBs);
     j=0;
     program->basicblock[j].start = 0;
     for(i=1; i< program->numOfIns; i++){
         if(program->leader[i]==1){
              program->basicblock[j].end = i-1;
              j++;
              program->basicblock[j].start = i;
         }
     }
     program->basicblock[j].end = i-1;
     // hieu chinh lai cac BBs, loai nhan va cac directive
     for(k =0 ; k < program->numOfBBs; k++)
     {
        // tang start
        while(program->ASMCode[program->basicblock[k].start][strlen(program->ASMCode[program->basicblock[k].start])-1]==':'
              || program->ASMCode[program->basicblock[k].start][0]=='.') //&& program->basicblock[k].start < program->basicblock[k].end)
                program->basicblock[k].start++;
        // giam end
        while(strcmp(program->ASMCode[program->basicblock[k].end],"nop")==0
              ||isJump(program->ASMCode[program->basicblock[k].end])>0
              ||program->ASMCode[program->basicblock[k].end][0]=='.')
              //&& program->basicblock[k].start < program->basicblock[k].end)
                program->basicblock[k].end--;
     }
}

// in cac basic block ra file output
void outBBToFile(char* outputFile, struct Program program)
{
     FILE *output;
     output = fopen(outputFile,"w");
     fprintf(output,"%s",program.directive);
     int i,k;
     for(k =0 ; k < program.numOfBBs; k++)
     {
        fprintf(output,"\nB%d:\n",k);
        for(i=program.basicblock[k].start; i<=program.basicblock[k].end; i++)
        {
                 fprintf(output,"%s\n",program.ASMCode[i]);
                 //printf("lenh thu %d: %s \n",i,program.ASMCode[i]);
        }
     }
     fclose(output);
}
void outProgramScheduledToFile(char* outputFile, struct Program program, struct DFG dfg[])
{
     FILE *output;
     output = fopen(outputFile,"w");
     fprintf(output,"%s\n",program.directive);
     int i,k;
     i=0;
      for(k =0 ; k < program.numOfBBs; k++)
     {
        if(program.basicblock[k].start >= program.basicblock[k].end)
              continue;
        while(i<program.basicblock[k].start)
        {
            fprintf(output,"%s\n",program.ASMCode[i]);
            i++;
        }
        for(i=program.basicblock[k].start; i<=program.basicblock[k].end; i++)
        {
            int index = dfg[k].schedule[i-program.basicblock[k].start] +program.basicblock[k].start;
            fprintf(output,"%s\n",program.ASMCode[index]);
                 //printf("lenh thu %d: %s \n",i,program.ASMCode[i]);
        }
     }
     while(i<program.numOfIns)
     {
            fprintf(output,"%s\n",program.ASMCode[i]);
            i++;
     }
     fclose(output);
}
// them ngay 15-11
void outProgramToFile(char* outputFile, struct Program program)
{
     FILE *output;
     output = fopen(outputFile,"w");
     fprintf(output,"%s\n",program.directive);
     int i;
     for(i = 0 ; i < program.numOfIns; i++)
     {
         fprintf(output,"%s\n",program.ASMCode[i]);
     }
     fclose(output);
}
//------------------------------------------------------------------

/*
int main()
{
    struct Program ex;
    inputProgram("asm.txt",&ex);
    BBpartition(&ex);
    //outBBToFile("BBAsm.txt",ex);
    outBBToFile2("bsrch2.txt",ex);
    //system("pause");
}
*/


