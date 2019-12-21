#include <stdio.h>
#include <string.h>
#include "DFG.h"
#include "Program.h"
#include "Scheduling.h"
int dd[MAX_NODES];
//#include "pisa.h"
//-------------------------------------
int allNodesScheduled(struct List list, struct DFG dfg, char* schedule)
{
     int i;
     // chi so cua lenh dau tien cua basic block
     //int start_index = dfg.program->basicblock[dfg.BB_index].start;

     if(strcmp(schedule,"ASAP")==0){
         for(i=0; i <list.numOfElem;i++)
              if( dfg.node[list.Elem[i]].ASAP_value == -1)return 0;
         return 1;
     }
     else if(strcmp(schedule,"ALAP")==0){
             for(i=0; i <list.numOfElem;i++)
                   if( dfg.node[list.Elem[i]].ALAP_value == -1)return 0;
             return 1;
     }
}
//---------------------
/*
int allScheduled(struct DFG dfg)
{
        int i;
        for(i=0; i <dfg.numOfNode;i++)
            if( dfg.node[i].assigned_value == -1)return 0;
        return 1;
}  //*/
//-----------------------------------------
void ASAP(struct DFG *dfg)
{
     int i,j,max,tmp;
     //int start_index = dfg->program->basicblock[dfg->BB_index].start;
     struct List V;
     init(&V);
     for(i=0; i < dfg->numOfNode; i++ )
          add(&V,i);
     //-------------------------------------------
     for(i=0 ; i < dfg->numOfNode; i++)
           if(dfg->node[i].pred.numOfElem == 0)  // neu node khong co cha thi ASAP = 1
                dfg->node[i].ASAP_value = 0;
            else
                dfg->node[i].ASAP_value = -1;

     while(allNodesScheduled(V,*dfg,"ASAP")==0)
     {
          for(i=0 ; i < dfg->numOfNode; i++)
             if((dfg->node[i].ASAP_value ==-1) && (allNodesScheduled(dfg->node[i].pred,*dfg,"ASAP")==1))
             {
                 max = 0;
                 for(j=0; j < dfg->node[i].pred.numOfElem; j++)
                 {
                          tmp = dfg->node[dfg->node[i].pred.Elem[j]].ASAP_value;
                          if(max < tmp)
                             max = tmp;
                 }
                 dfg->node[i].ASAP_value = max + 1;
             }
     }

}
//--------------------------------------------------------------
void ALAP(struct DFG *dfg)
{
     int i,j,min,tmp;
     //int start_index = dfg->program->basicblock[dfg->BB_index].start;
     //int Tmax = 1000;
     int Tmax = dfg->numOfNode;
     struct List V;
     init(&V);
     for(i=0; i < dfg->numOfNode; i++ )
          add(&V,i);
     //-------------------------------------------
     for(i=0 ; i < dfg->numOfNode; i++)
           if(dfg->node[i].succ.numOfElem == 0)  // neu node khong co con thi ALAP = Tmax
                dfg->node[i].ALAP_value = Tmax-1;
            else
                dfg->node[i].ALAP_value = -1;

     while(allNodesScheduled(V,*dfg,"ALAP")==0)
     {
          for(i=0 ; i < dfg->numOfNode; i++)
             if(dfg->node[i].ALAP_value ==-1 && allNodesScheduled(dfg->node[i].succ,*dfg,"ALAP")==1)
             {
                 min = Tmax;
                 for(j=0; j < dfg->node[i].succ.numOfElem; j++)
                 {
                          tmp = dfg->node[dfg->node[i].succ.Elem[j]].ALAP_value;
                          if(min > tmp)
                             min = tmp;
                 }
                 dfg->node[i].ALAP_value = min - 1;
             }
     }
     //*
     min = Tmax;
     for(i=0 ; i < dfg->numOfNode; i++)
         if(min > dfg->node[i].ALAP_value) min = dfg->node[i].ALAP_value;
     for(i=0 ; i < dfg->numOfNode; i++)
         dfg->node[i].ALAP_value = dfg->node[i].ALAP_value - min;
      //*/

}
//---------------------------------------------------
void countSucc(struct DFG dfg,struct Node node,int * count)
{
    int i;
    if(node.succ.numOfElem>0)
        for(i=0;i<node.succ.numOfElem;i++)
        {
            int index = node.succ.Elem[i];
            if(dd[index]==0)
            {
                dd[index]=1;
                (*count)++;
                countSucc(dfg,dfg.node[index],count);
            }
        }
}
//---------------------------------------------------
void countSucc2(struct DFG dfg,struct Node node,int * count)
{
    int i,index;
    int tmp,result;
    struct List Q;
    init(&Q);
    result = 0;
    if(node.succ.numOfElem>0)
    {
        for(i=0;i<node.succ.numOfElem;i++)
        {
            index = node.succ.Elem[i];
            if(dd[index]==0)
            {
                add(&Q,index);
                dd[index]=1;
            }
        }

        while(Q.numOfElem>0)
        {
            tmp = getElem(&Q,0);
            result++;
            del(&Q,tmp);
            for(i=0;i<dfg.node[tmp].succ.numOfElem;i++)
            {
                index = dfg.node[tmp].succ.Elem[i];
                if(dd[index]==0)
                {
                    add(&Q,index);
                    dd[index]=1;
                }
            }
        }
    }
    (*count) = result;
}
//--------------------------
void countPred(struct DFG dfg,struct Node node,int * count)
{
    int i;
    if(node.pred.numOfElem>0)
        for(i=0;i<node.pred.numOfElem;i++)
        {
            int index = node.pred.Elem[i];
            if(dd[index]==0)
            {
                dd[index]=1;
                (*count)++;
                countPred(dfg,dfg.node[index],count);
            }
        }
}
//---------------------------------------------------
void countPred2(struct DFG dfg,struct Node node,int * count)
{
    int i,index;
    int tmp,result;
    struct List Q;
    init(&Q);
    result = 0;
    if(node.pred.numOfElem>0)
    {
        for(i=0;i<node.pred.numOfElem;i++)
        {
            index = node.pred.Elem[i];
            if(dd[index]==0)
            {
                add(&Q,index);
                dd[index]=1;
            }
        }

        while(Q.numOfElem>0)
        {
            tmp = getElem(&Q,0);
            result++;
            del(&Q,tmp);
            for(i=0;i<dfg.node[tmp].pred.numOfElem;i++)
            {
                index = dfg.node[tmp].pred.Elem[i];
                if(dd[index]==0)
                {
                    add(&Q,index);
                    dd[index]=1;
                }
            }
        }
    }
    (*count) = result;
}
//------------------------------------------------
void ASAP2(struct DFG *dfg)
{
     int i,j;
     //int start_ins = dfg->program->basicblock[dfg->BB_index].start;
     int count;
     for(i=0;i < dfg->numOfNode;i++)
        dfg->node[i].ASAP_value = -1;
     for(i=0;i < dfg->numOfNode;i++)
     {
          if(dfg->node[i].ASAP_value == -1)
          {
              count = 0;
              for(j=0;j<MAX_NODES;j++)dd[j]=0;
              countPred2(*dfg,dfg->node[i],&count);
              dfg->node[i].ASAP_value = count;
          }
     }

}
//--------------------------------------------------------------
void ALAP2(struct DFG *dfg)
{
     int i,j;
     int Tmax = dfg->numOfNode;
     //int start_ins = dfg->program->basicblock[dfg->BB_index].start;
     int count;
     for(i=0;i < dfg->numOfNode;i++)
        dfg->node[i].ALAP_value = -1;
     for(i=0;i < dfg->numOfNode;i++)
     {
          if(dfg->node[i].ALAP_value == -1)
          {
              count = 0;
              for(j=0;j<MAX_NODES;j++)dd[j]=0;
              countSucc2(*dfg,dfg->node[i],&count);
              dfg->node[i].ALAP_value = Tmax - count -1;
          }
     }

}

//--------------------------------------------------
void inputPDT()
{
    printf("running inputPDT\n");
    double x[144];
    FILE *input;
    input = fopen("PDT2.txt","r");
    int i,j,index;
    for(i=0;i<144;i++)
        fscanf(input,"%lf",&x[i]);
    for(i=0;i<12;i++)
        for(j=0;j<12;j++)
        {
            index=i*12+j;
            PDT[i][j]=x[index];
        }
}
//-----------------------------------------
// Force-directed Scheduling for low Power
void FDS(struct DFG *dfg)
{
    int i,j;
    double self_force,ps_force, total_force, min_force;
    int min_step, min_node;
    int step[dfg->numOfNode];
    for(i=0;i<dfg->numOfNode;i++)
        step[i] = -1;
    //---------
    ASAP2(&dfg);
    ALAP2(&dfg);
    // ban dau
    for(i=0;i<dfg->numOfNode;i++)
       if(dfg->node[i].ALAP_value==dfg->node[i].ASAP_value)
          dfg->node[i].assigned_value = dfg->node[i].ASAP_value;
       else
          dfg->node[i].assigned_value = -1;

    for(i=0;i<dfg->numOfNode;i++)
        if(dfg->node[i].assigned_value==-1)
        {
            for(j=dfg->node[i].ASAP_value; j <= dfg->node[i].ALAP_value ;j++)
            {
                //dfg->node[i].assigned_value = j;
                if(step[j]!=-1)// chua co lenh nao phan vao step nay
                {
                    int tmpStep[dfg->numOfNode];
                    for(i=0;i<dfg->numOfNode;i++)
                        tmpStep[i] = step [i];
                    int pre = j-1;
                    if(step[pre]!=-1) // da duoc phan, ta biet luon lenh dung truoc
                    {

                    }
                    else // truoc no chua co lenh nao
                    {

                    }



                }
                    // tinh self_fore
                    // tinh ps_force
                    // total_force = self_force + ps_force


            } //end for

                // xac dinh min force (ins, step)
                // dfg->node[i].assigned_value = step
                // update ASAP
                // update ALAP
        } // end for

}
//-----------------------------------------
void ListSchedule(struct DFG *dfg)
{
    int i,j;
    for(i=0;i<dfg->numOfNode;i++)
        dfg->schedule[i] = -1;
    for(i=0;i<dfg->numOfNode;i++)
       if(dfg->node[i].ALAP_value==dfg->node[i].ASAP_value)
       {
          dfg->node[i].assigned_value = dfg->node[i].ASAP_value;
          dfg->schedule[dfg->node[i].ASAP_value] = i;
       }
       else
          dfg->node[i].assigned_value = -1;
    //----------
    dfg->node[0].assigned_value =0;
    dfg->schedule[0] = 0;
    for(i=1;i<dfg->numOfNode;i++)
    {
        for(j=0;j<dfg->numOfNode;j++)
            if(dfg->node[j].ASAP_value<i && dfg->node[j].assigned_value == -1)
                dfg->node[j].ASAP_value = i;
        if(dfg->schedule[i] == -1)
        {
            double minPDT=5000000;
            int min_index;
            for(j=0;j<dfg->numOfNode;j++)
            {
                //printf("step %d not %d ASAP %d ALAP %d \n",i,j,dfg->node[j].ASAP_value,dfg->node[j].ALAP_value);
                if(dfg->node[j].ASAP_value <= i && dfg->node[j].ALAP_value >= i
                    && dfg->node[j].assigned_value == -1)
                {
                     int index1 = indexOf(dfg->program->ASMCode[dfg->node[dfg->schedule[i-1]].ins_index]);
                     int index2 = indexOf(dfg->program->ASMCode[dfg->node[j].ins_index]);
                    // printf("xet not %d index1 %d index2 %d--- PDT %10.4f \n",j,index1,index2,PDT[index1][index2]);
                     if(i == dfg->node[j].ALAP_value )
                     {
                         minPDT = PDT[index1][index2];
                         min_index = j;
                         //printf("not %d break \n",j);
                         break;
                     }
                     if(PDT[index1][index2] < minPDT)
                     {
                         minPDT = PDT[index1][index2];
                         min_index = j;
                     }
                }
            }
            dfg->schedule[i] = min_index;
            dfg->node[min_index].assigned_value = i;
            //printf("node %d i=%d ASAP %d ALAP %d\n",min_index,i,dfg->node[min_index].ASAP_value,dfg->node[min_index].ALAP_value);
           // printf("-----------step %d --- node %d \n",i,min_index);
        }
    }
}
//------------------------
void ListSchedule2(struct DFG *dfg)
{
    int i,j,k;
    struct List readyList;
    init(&readyList);
    for(i=0;i<dfg->numOfNode;i++)
        dfg->schedule[i] = -1;
    for(i=0;i<dfg->numOfNode;i++)
          dfg->node[i].assigned_value = -1;
    //----------
    dfg->node[0].assigned_value =0;
    dfg->schedule[0] = 0;
    for(i=1;i<dfg->numOfNode;i++)
    {
        if(dfg->schedule[i] == -1)
        {
            double minPDT=5000000;
            int min_index;
            // add cac node( ma tat ca cha da duoc phan) va readyList
            for(j=0;j<dfg->numOfNode;j++)
            {
                if(dfg->node[j].assigned_value != -1) continue;
                int isReady = 1;
                for(k=0;k<dfg->node[j].pred.numOfElem;k++)
                    if(dfg->node[dfg->node[j].pred.Elem[k]].assigned_value == -1)
                    {
                        isReady = 0;
                        break;
                    }
                if(isReady==1 && contain(&readyList,j)==0)
                    add(&readyList,j);
            }
            // tim node tiep theo trong readyList
            for(j=0;j<readyList.numOfElem;j++)
            {
                int index1 = indexOf(dfg->program->ASMCode[dfg->node[dfg->schedule[i-1]].ins_index]);
                int index2 = indexOf(dfg->program->ASMCode[dfg->node[readyList.Elem[j]].ins_index]);

                if(PDT[index1][index2] < minPDT)
                {
                         minPDT = PDT[index1][index2];
                         min_index = readyList.Elem[j];
                }
            }
            dfg->schedule[i] = min_index;
            dfg->node[min_index].assigned_value = i;
            del(&readyList,min_index);
        } // end if
    }// end for
}
//------------------------
// mang de danh dau
int a[MAX_NODES];
//-----------------
void sort2(int i, struct DFG* dfg,struct List* init_list, struct List* result_list,struct List* tmp_list,double* min_power)
{
    int j;
    for(j=0;j<init_list->numOfElem;j++)
        if(a[j]==0)
        {
            a[j] = 1;
            tmp_list->Elem[i] = init_list->Elem[j];
            if(i == init_list->numOfElem-1)  //check ket qua
            {
                double tmp_power;
                int k;
                for(k=0;k<i;k++)
                {
                    int index1 = indexOf(dfg->program->ASMCode[dfg->program->basicblock[dfg->BB_index].start+tmp_list->Elem[k]]);
                    int index2 = indexOf(dfg->program->ASMCode[dfg->program->basicblock[dfg->BB_index].start+tmp_list->Elem[k+1]]);
                    tmp_power += PDT[index1][index2];
                }
                if(tmp_power < *min_power)
                {
                    *min_power = tmp_power;
                    init(result_list);
                    for(k=0;k<=i;k++)
                        add(result_list,tmp_list->Elem[k]);
                    printf("result:\n");
                    for(k=0;k<=i;k++)
                    printf("%d ",result_list->Elem[k]);
                    printf("\n");
                }
            }
            else sort2(i+1,dfg,init_list,result_list,tmp_list,min_power);
            a[j] = 0;
        }

}
//-----------
void schedule2(struct DFG *dfg)
{
    //*
    int i,j;
    for(i=0;i<dfg->numOfNode;i++)
        dfg->schedule[i] = -1;
    //-----
    int max_ASAP = 0;  // tim level lon nhat
    for(i=0;i<dfg->numOfNode;i++)
    {
        if(max_ASAP < dfg->node[i].ASAP_value)
                max_ASAP = dfg->node[i].ASAP_value;
    }
    //----
    int index = 0;
    //----
    // lap lich tung nhom nho ung voi tung level
    for(i=0;i<=max_ASAP;i++) // chu y la nho hon hoac bang
    {
        struct List V,Q,tmp_list;
        init(&V);
        init(&Q);
        init(&tmp_list);
        for(j=0;j<dfg->numOfNode;j++)
            if(dfg->node[j].ASAP_value==i)
                add(&V,j);
        if(V.numOfElem==1)
        {
            dfg->schedule[index] = V.Elem[0];
            index++;
        }
        else
        {
            for(j=0;j<dfg->numOfNode;j++)
                    a[j]=0;
            double min_power = 0;
            for(j=0;j<V.numOfElem-1;j++)
            {
                int index1 = indexOf(dfg->program->ASMCode[dfg->program->basicblock[dfg->BB_index].start+V.Elem[j]]);
                int index2 = indexOf(dfg->program->ASMCode[dfg->program->basicblock[dfg->BB_index].start+V.Elem[j+1]]);
                min_power += PDT[index1][index2];
            }
            for(j=0;j<V.numOfElem;j++)
                add(&Q,V.Elem[j]);
            sort2(0,&dfg,&V,&Q,&tmp_list,&min_power);
            for(j=0;j<V.numOfElem;j++)
            {
                dfg->schedule[index] = Q.Elem[j];
                dfg->node[Q.Elem[j]].assigned_value = index;
                index++;
            }
        }
    } //*/
    printf("%s",dfg->program->ASMCode[100]);
}
void improveScheduling(struct DFG *dfg)
{
    int i,j,k;
    //int node_i,node_j;
    int tmp_schedule[dfg->numOfNode];
    int index1,index2,index3,index4;
    double tmp_power,current_power;
    int tmp_index;
    for(i=0;i<dfg->numOfNode;i++)
        for(j=0;j<dfg->numOfNode;j++)
        {
            if(i > dfg->node[dfg->schedule[j]].ASAP_value
               && i < dfg->node[dfg->schedule[j]].ALAP_value
               && j > dfg->node[dfg->schedule[i]].ASAP_value
               && j < dfg->node[dfg->schedule[i]].ALAP_value && i!=j)
              {
                  current_power = 0;
                  tmp_power = 0;
                  for(k=0;k<dfg->numOfNode;k++)
                    if(k==i)
                        tmp_schedule[k] = dfg->schedule[j];
                    else if(k==j)
                        tmp_schedule[k] = dfg->schedule[i];
                    else tmp_schedule[k] = dfg->schedule[k];
                  for(k=0; k < dfg->numOfNode-1;k++)
                  {
                      index1 =  indexOf(dfg->program->ASMCode[dfg->node[dfg->schedule[k]].ins_index]);
                      index2 =  indexOf(dfg->program->ASMCode[dfg->node[dfg->schedule[k+1]].ins_index]);
                      current_power += PDT[index1][index2];
                      index3 =  indexOf(dfg->program->ASMCode[dfg->node[tmp_schedule[k]].ins_index]);
                      index4 =  indexOf(dfg->program->ASMCode[dfg->node[tmp_schedule[k+1]].ins_index]);
                      tmp_power += PDT[index3][index4];
                  }
                  if(tmp_power < current_power)
                  {
                      printf("BB %d \n",dfg->BB_index);
                      printf("hehe i %d - j %d \n",i,j);
                      tmp_index = dfg->schedule[i];
                      dfg->schedule[i] = dfg->schedule[j];
                      dfg->schedule[j] = tmp_index;
                      dfg->node[dfg->schedule[i]].assigned_value = i;
                      dfg->node[dfg->schedule[j]].assigned_value = j;
                  }
              }
        }
}

