#include <stdio.h>
#include <string.h>
#include "Program.h"
#include "BasicBlockPartition.h"
//#include "List.h"  // khong can include vi trong DFG.h da include roi
#include "DFG.h"

//-----------------------------------------------
void initNode(struct Node* node)
{
     node->ins_index = -1;
     node->ASAP_value = -1;
     node->ALAP_value = -1;
     node->assigned_value = -1;
     init(&(node->pred));
     init(&(node->succ));
}
int containsBracket(char* ins)
{
    int i;
    for(i=0;i<strlen(ins);i++)
        if(ins[i]=='(' || ins[i]==')')
            return 1;
    return 0;
}
// tra lai thanh ghi ma lenh ins doc tu do'
//char read[2][10];
void ReadFrom(struct Program program, int ins_index)
{
     int i,j,k;
     i=0;
     char c[10],tmp;
     //lay loai lenh
     for(j=0;j<strlen(program.ASMCode[ins_index]);j++)
     {
         tmp = program.ASMCode[ins_index][j];
         if(tmp!=' '&& tmp!='\t')
         {
             c[i]= tmp;
             i++;
         }
         else break;
     }
     c[i]='\0';
     i=0;
     if(strcmp(c,"sw")==0 || strcmp(c,"mult")==0)
     {
         while(program.ASMCode[ins_index][j]!='$' && j<strlen(program.ASMCode[ins_index]))
         {
            j++;
         }
         tmp = program.ASMCode[ins_index][j];
         while(tmp!=' '&&tmp!='\t'&&tmp!='\n' &&tmp!=','&& i < 10)
         {
               read[0][i]=tmp;
               i++;
               j++;
               tmp = program.ASMCode[ins_index][j];
         }
         read[0][i]='\0';
         i=0;
         while(program.ASMCode[ins_index][j]!='$' && j<strlen(program.ASMCode[ins_index]))
            {
                j++;
            }
         tmp = program.ASMCode[ins_index][j];
         while(tmp!=' ' && tmp!='\t' && tmp!=',' && tmp!=')' &&tmp!='\0')
         {
               read[1][i]=tmp;
               i++;
               j++;
               tmp = program.ASMCode[ins_index][j];
         }
         read[1][i]='\0';
         i=0;
     }
     else if(strcmp(c,"lw")==0)  //them ngay 17-9
     {
         while(program.ASMCode[ins_index][j]!=',' && j<strlen(program.ASMCode[ins_index]))
         {
            j++;
         }
         j++;
         tmp = program.ASMCode[ins_index][j];
         while(tmp!=' '&&tmp!='\t'&&tmp!=',' &&tmp!='\0')
         {
               read[0][i]=tmp;
               i++;
               j++;
               tmp = program.ASMCode[ins_index][j];
         }
         read[0][i]='\0';
         i=0;
         k=0;
         while(read[0][k]!='$' && k<strlen(read[0]))
         {
            k++;
         }
         tmp = read[0][k];
         while(tmp!=' '&&tmp!='\t'&&tmp!=',' &&tmp!=')' &&tmp!='\0')
         {
               read[1][i]=tmp;
               i++;
               k++;
               tmp = read[0][k];
         }
         read[1][i]='\0';
     }
     else
     {

         while(program.ASMCode[ins_index][j]!='$' && j<strlen(program.ASMCode[ins_index]))
         {
            j++;
         }
         if(j<strlen(program.ASMCode[ins_index]))j++;
         while(program.ASMCode[ins_index][j]!='$' && j<strlen(program.ASMCode[ins_index]))
         {
            j++;
         }
         tmp = program.ASMCode[ins_index][j];
         while(tmp!=' '&&tmp!='\t'&&tmp!=',' &&tmp!=')' &&tmp!='\0')
         {
               read[0][i]=tmp;
               i++;
               j++;
               tmp = program.ASMCode[ins_index][j];
         }
         read[0][i]='\0';
         i=0;
         while(program.ASMCode[ins_index][j]!='$' && j<strlen(program.ASMCode[ins_index]))
         {
            j++;
         }
         tmp = program.ASMCode[ins_index][j];
         while(tmp!=' ' && tmp!='\t' && tmp!=',' && tmp!=')' &&tmp!='\0')
         {
               read[1][i]=tmp;
               i++;
               j++;
               tmp = program.ASMCode[ins_index][j];
         }
         read[1][i]='\0';
         i=0;
     }

}
//-----------------------------------------------
// tra lai thanh ghi ma lenh ins ghi vao no
//char write[10];
char* WriteTo(struct Program program, int ins_index)
{
     //--
     int i,j;
     char c[10],tmp;
     i=0;
     // lay loai lenh
     for(j=0;j<strlen(program.ASMCode[ins_index]);j++)
     {
         tmp = program.ASMCode[ins_index][j];
         if(tmp!=' '&& tmp!='\t')
         {
             c[i]= tmp;
             i++;
         }
         else break;
     }
     c[i]='\0';
     i=0;

     if(strcmp(c,"mult")==0)
     {
         write[i]='\0';
         i=0;
     }
     else if(strcmp(c,"sw")==0)  // them ngay 17-9
     {

            while(program.ASMCode[ins_index][j]!=',' && j<strlen(program.ASMCode[ins_index]))
            {
                j++;
            }
            j++;
            tmp = program.ASMCode[ins_index][j];
            while(tmp!=' ' && tmp!='\t' && tmp!=',' &&tmp!='\0')
            {
                    write[i]=tmp;
                    i++;
                    j++;
                    tmp = program.ASMCode[ins_index][j];
            }
            write[i]='\0';
            i=0;
     }
     else
     {
            while(program.ASMCode[ins_index][j]!='$' && j<strlen(program.ASMCode[ins_index]))
            {
                j++;
            }
            tmp = program.ASMCode[ins_index][j];
            while(tmp!=' ' && tmp!='\t' && tmp!=',' && tmp!=')' &&tmp!='\0')
            {
                    write[i]=tmp;
                    i++;
                    j++;
                    tmp = program.ASMCode[ins_index][j];
            }
            write[i]='\0';
            i=0;
     }
     return write;
}

//-----------------------------------------------------------

void constructDFG(struct Program program, int BB_index, struct DFG *dfg)
{
     dfg->program = &program;
     dfg->BB_index = BB_index;
     dfg->numOfNode = program.basicblock[BB_index].end
      - program.basicblock[BB_index].start + 1;
     //dfg->node = (struct Node*)malloc(dfg->numOfNode);
     int i,j;
     char* tmp_write;
     for(i=0; i < dfg->numOfNode; i++)
     {
          initNode(&dfg->node[i]);
          dfg->node[i].ins_index = i+program.basicblock[BB_index].start;
          dfg->schedule[i]=-1;
     }
     //------------------------------------------
     int a[dfg->numOfNode][dfg->numOfNode];
     for(i=0; i < dfg->numOfNode; i++)
        for(j=0; j < dfg->numOfNode; j++)
            a[i][j]=0;
     //-------------------------------------------------------------
     for(i=0; i < dfg->numOfNode; i++)
     {
          //printf("%s \n",program.ASMCode[i+program.basicblock[BB_index].start]);
          tmp_write = WriteTo(program,i+program.basicblock[BB_index].start);
          char write[10];  // phai luu sang xau khac vi gia tri xau tmp_write se bi thay doi o lan goi ham sau
          // dia tri con tro tmp_write la ko doi nhung noi dung bi thay doi
          for(j=0;j<strlen(tmp_write);j++)
               write[j]=tmp_write[j];
          write[j]='\0';
          // code them ngay 18-9, xu li cho lw $31
          int l=0;
          char c[6],tmp;
          for(j=0;j<strlen(program.ASMCode[i+program.basicblock[BB_index].start]);j++)
          {
                tmp = program.ASMCode[i+program.basicblock[BB_index].start][j];
                if(tmp!=' '&& tmp!='\t')
                {
                    c[l]= tmp;
                    l++;
                }
                else break;
            }
            c[l]='\0';

          if(strcmp(write,"")!=0)
              for(j=i+1; j < dfg->numOfNode; j++)
              {
                    char* tmp_write2 = WriteTo(program,j+program.basicblock[BB_index].start);
                    if(strcmp(write,tmp_write2)==0) // WAW
                    {
                        a[i][j]=1;
                        //printf("---%s WAW\n",program.ASMCode[j+program.basicblock[BB_index].start]);
                        break;
                    }
                    // code them 18-9,  xu li cho lw $31
                    if(strcmp(c,"lw")==0 && strcmp(write,"$31")==0 && strcmp(tmp_write2,"$fp")==0)
                    {
                        a[i][j] =1;
                    }
                    ReadFrom(program,j+program.basicblock[BB_index].start);
                    if(strcmp(write,read[0])==0 || strcmp(write,read[1])==0 )  //RAW
                    {
                        //printf("---%s RAW\n",program.ASMCode[j+program.basicblock[BB_index].start]);
                        a[i][j]=1;
                    }
              }
          ReadFrom(program,i+program.basicblock[BB_index].start);  //WAR
          int k;
          for(k=0;k<2;k++)
              if(strcmp(read[k],"")!=0)
                    for(j=i+1; j < dfg->numOfNode; j++)
                    {
                            char* tmp_write2 = WriteTo(program,j+program.basicblock[BB_index].start);
                            if(strcmp(tmp_write2,read[k])==0 )
                            {
                                 a[i][j]=1;
                                 //printf("---%s WAR\n",program.ASMCode[j+program.basicblock[BB_index].start]);
                                 break;
                            }
                    }
     }
     for(i=0; i < dfg->numOfNode; i++)
        for(j=0; j < dfg->numOfNode; j++)
           if(a[i][j]==1 && (j-i)>1)
           {
               int  k=j,tmp=j;
               int l;
               while(k!=i)
               {
                  for(l=k-1;l>=i;l--)
                     if(a[l][k]==1 && (l!=i || k!=j))  // chu y cai nay
                     {
                         k=l;
                         break;
                     }
                  if(k==tmp) break;
                    else tmp = k;
               }
               if(k==i)a[i][j]=0;
           }
     for(i=0; i < dfg->numOfNode; i++)
        for(j=0; j < dfg->numOfNode; j++)
            if(a[i][j]==1)
            {
                  add(&dfg->node[i].succ,j);
                  add(&dfg->node[j].pred,i);
            }
}
//-------------------------------------------------------------
// viet chieu t3 28-2
void outDFGToFile(char* filename, struct DFG dfg)
{
     FILE *output;
     output = fopen(filename,"w");
     fprintf(output,"%d\n",dfg.BB_index);
     fprintf(output,"%d\n",dfg.numOfNode);

     int i,j,k,tmp;

     for(i=0; i<dfg.numOfNode; i++)
     {
        for(j=0; j<dfg.numOfNode; j++)
        {
           tmp = 0;
           for(k=0; k<dfg.node[i].succ.numOfElem; k++)
               if(dfg.node[i].succ.Elem[k]==j)
               {
                    tmp=1;  //j la con i
                    break;
               }

           fprintf(output,"%d",tmp);  //neu j la con i thi in ra 1, ko thi in ra 0
           if(j<dfg.numOfNode-1)   fprintf(output," ");
           else fprintf(output,"\n");
        }
     }
     fclose(output);
}
//-------------------------------------------------------------
void inputDFGFromFile(char* filename, struct Program program, struct DFG *dfg)
{
     FILE *input;
     input = fopen(filename,"r");
     int i,j,tmp;
     dfg->program = &program;
     fscanf(input,"%d",&dfg->BB_index);

     fscanf(input,"%d",&dfg->numOfNode);

     //dfg->node = (struct Node*)malloc(7);
     for(i=0; i<dfg->numOfNode; i++)
     {
              initNode(&dfg->node[i]);
              dfg->node[i].ins_index = dfg->program->basicblock[dfg->BB_index].start + i;
     }

     for(i=0; i<dfg->numOfNode; i++)
     {
        for(j=0; j<dfg->numOfNode; j++)
        {
             fscanf(input,"%d",&tmp);
             if(tmp==1)
             {
                  add(&dfg->node[i].succ,j);
                  add(&dfg->node[j].pred,i);

             }
        }
     }
     fclose(input);
}
/*
int main()
{
    struct Program ex;
    inputProgram("asm.txt",&ex);
    BBpartition(&ex);
    int i;
    outBBToFile2("bsrch2.txt",ex);
    char* _write;// = (char*)malloc(10);;
    for(i=ex.basicblock[0].start; i<=ex.basicblock[0].end; i++)
    {
        printf("%d %s\n",i,ex.ASMCode[i]);
        _write = WriteTo(ex,i);
        if(strcmp(_write,"")!=0)
          printf("write: %s \n",_write);
        ReadFrom(ex,i);
        if(strcmp(read[0],"")!=0)
          printf("read 0: %s \n",read[0]);
        if(strcmp(read[1],"")!=0)
          printf("read 1: %s \n",read[1]);
    }
    struct DFG dfg;
    constructDFG(ex,0,&dfg);
    outDFGToFile("dfg.txt",dfg);
    //system("pause");
}
*/
