#include "Genetic.h"
#include "DFG.h"
//#include "pisa.h"
#include "Scheduling.h"
#include "Program.h"
#include <stdlib.h>

void createRandomPriorities(struct Chromosome* chro, int randSeed)
{
    int i,j,k,pri;
    int tmp[MAX_NODES]; // mang de danh dau
    for(i=0;i<chro->num_of_gene;i++)
    {
        tmp[i] = -1;
        chro->prio[i] = -1;
    }
    srand(randSeed);
    for(i=0;i<chro->num_of_gene;i++)
    {
        pri = rand()%(chro->num_of_gene);
        if(tmp[pri]==-1)
        {
            chro->prio[i] = pri;
            tmp[pri] = 1;
        }
        else  // tmp[pri] ==1
        {
            j = pri;
            k = pri;
            while(chro->prio[i] == -1)
            {
                if(j>0)j = j - 1;
                if(k<(chro->num_of_gene-1)) k = k + 1;
                if(tmp[j]== -1)
                {
                    chro->prio[i] = j;
                    tmp[j] = 1;
                }
                else if(tmp[k]== -1)
                {
                    chro->prio[i] = k;
                    tmp[k] = 1;
                }
            }
        }
    }
}
//---------------------------------------
int equal(struct Chromosome* chro1, struct Chromosome* chro2)
{
        int i;
        for(i=0;i<chro1->num_of_gene;i++)
            if(chro1->prio[i]!=chro2->prio[i])
                return 0;
        return 1;

}

// dot bien
void mutation(struct Chromosome* chro1, struct Chromosome* chro2)
{
    int i,j,tmp;
    chro2->num_of_gene = chro1->num_of_gene;
    for(i=0;i<chro1->num_of_gene;i++)
        chro2->prio[i] = chro1->prio[i];
    //srand(randSeed);
    i = rand()%(chro2->num_of_gene);
    j = rand()%(chro2->num_of_gene);
    while(i==j)
    {
        j = rand()%(chro2->num_of_gene);
    }
    tmp = chro2->prio[i];
    chro2->prio[i] = chro2->prio[j];
    chro2->prio[j] = tmp;
}

// lai ghep
void crossOver(struct Chromosome* chro1,struct Chromosome* chro2,struct Chromosome* C)
{
    int i,j,tmp;
    int x,y; // random gene from
    struct List tmpList1,tmpList2;
    init(&tmpList1);
    init(&tmpList2);
    C->num_of_gene = chro1->num_of_gene;
    //srand(randSeed);
    x = rand()%(chro1->num_of_gene);
    y = rand()%(chro1->num_of_gene);
    while(x==y)
    {
        y = rand()%(chro1->num_of_gene);
    }
    if(x>y)
    {
        tmp = x;
        x = y;
        y = tmp;
    }
    //printf("\nx %d -- y %d",x,y);
    //------------------
    for(i=x;i<=y;i++)
        add(&tmpList1,chro1->prio[i]);
    for(i=0;i<chro2->num_of_gene;i++)
        if(contain(&tmpList1,chro2->prio[i])==0)
            add(&tmpList2,chro2->prio[i]);
    i=x;
    j=-1;
    while(tmpList1.numOfElem < chro1->num_of_gene)
    {
        if(i==0)
        {
            i = chro1->num_of_gene;
            i--;
            j++;
            if(chro1->prio[i] != tmpList2.Elem[j])
            {
                if(contain(&tmpList1,chro1->prio[i])==0)
                    add(&tmpList1,chro1->prio[i]);
                if(contain(&tmpList1,tmpList2.Elem[j])==0)
                    add(&tmpList1,tmpList2.Elem[j]);
            }
            else
                    add(&tmpList1,chro1->prio[i]);
        }
        else if(y==chro1->num_of_gene-1)
        {
            i--;
            j++;
            if(chro1->prio[i] != tmpList2.Elem[j])
            {
                if(contain(&tmpList1,chro1->prio[i])==0)
                    insert(&tmpList1,chro1->prio[i],0);
                if(contain(&tmpList1,tmpList2.Elem[j])==0)
                    insert(&tmpList1,tmpList2.Elem[j],0);
            }
            else
                insert(&tmpList1,chro1->prio[i],0);
        }
        else
        {
            i--;
            j++;
            if(chro1->prio[i] != tmpList2.Elem[j])
            {
                if(contain(&tmpList1,chro1->prio[i])==0)
                    insert(&tmpList1,chro1->prio[i],0);
                if(contain(&tmpList1,tmpList2.Elem[j])==0)
                    add(&tmpList1,tmpList2.Elem[j]);
            }
            else
                insert(&tmpList1,chro1->prio[i],0);
        }
    }
    C->num_of_gene = chro1->num_of_gene;
    for(i=0;i<C->num_of_gene;i++)
        C->prio[i] = tmpList1.Elem[i];
}
//------------------------------------------------------
void TopoSort(struct DFG* dfg, struct Chromosome* chro)
{
    int d[chro->num_of_gene];
    int i,j,tmp,count;
    int index = 0; // vi tri dang xet trong chuoi topo
    for(i=0;i<chro->num_of_gene;i++)
    {
        chro->topo[i] = -1;
        d[i] = -1;
    }
    struct List tmpList;
    init(&tmpList);
    // ban dau add nhung node ko co cha
    for(i=0;i<dfg->numOfNode;i++)
        if(dfg->node[i].pred.numOfElem == 0)
        {
            add(&tmpList,i);
        }
    // sap xep
    for(i=0;i<tmpList.numOfElem;i++)
        for(j=tmpList.numOfElem-1;j>i;j--)
            if(chro->prio[tmpList.Elem[j-1]]>chro->prio[tmpList.Elem[j]])
            {
                tmp = tmpList.Elem[j-1];
                tmpList.Elem[j-1] = tmpList.Elem[j];
                tmpList.Elem[j] = tmp;
            }
    // vong lap chinh
    while(tmpList.numOfElem>0)
    {
        chro->topo[index] = tmpList.Elem[0];
        index++;
        d[tmpList.Elem[0]] = 1;
        //printf("hehe del %d: \n",tmpList.Elem[0]);
        //for(i=0;i<tmpList.numOfElem;i++)
        //    printf("%d ",tmpList.Elem[i],chro->prio[tmpList.Elem[i]]);
        //printf("\n");
        del(&tmpList,tmpList.Elem[0]);
        //for(i=0;i<tmpList.numOfElem;i++)
        //    printf("%d ",tmpList.Elem[i],chro->prio[tmpList.Elem[i]]);
        //printf("\n");
        for(i=0;i<dfg->numOfNode;i++)
        {
            if(d[i]!=1)
            {
                count = 0;
                for(j=0;j<dfg->node[i].pred.numOfElem;j++)
                    if(d[dfg->node[i].pred.Elem[j]]!=1)
                        count++;
                if(count == 0 && contain(&tmpList,i)==0)
                {
                    add(&tmpList,i);
                    //printf("add %d \n",i);
                    for(j=tmpList.numOfElem-1;j>0;j--)
                        if(chro->prio[tmpList.Elem[j-1]]>chro->prio[tmpList.Elem[j]])
                        {
                            tmp = tmpList.Elem[j-1];
                            tmpList.Elem[j-1] = tmpList.Elem[j];
                            tmpList.Elem[j] = tmp;
                        }
                }
            }
        }
    }
}
//------------------------
void fitness(struct DFG* dfg, struct Chromosome* chro )
{
    double power_sum = 0;
    int i,index1,index2;
    for(i=0;i<chro->num_of_gene-1;i++)
    {
         index1 =  indexOf(dfg->program->ASMCode[dfg->node[chro->topo[i]].ins_index]);
         index2 =  indexOf(dfg->program->ASMCode[dfg->node[chro->topo[i+1]].ins_index]);
         power_sum += PDT[index1][index2];
    }
    chro->power = power_sum;
}
void Genetic_Schedule(struct DFG* dfg)
{
    int i,j,k,tmp;
    int pop_size = 2000; // so ca the trong quan the
    int max_gen = 400; //so the he sinh ra
    double pc = 0.8; // xac suat lai ghep
    double pm = 0.5;  //xac suat dot bien
    //int bestSolution = 0;
    struct Chromosome chro[pop_size*2];
    int a[pop_size*2];  // mang luu so thu tu cua cac NST de sap xep

    for(i=0;i<pop_size*2;i++)
    {
        chro[i].num_of_gene = dfg->numOfNode;
        chro[i].power = 0;
        a[i] = i;
    }
    for(i=0;i<pop_size;i++)
    {
        createRandomPriorities(&chro[i],time(0)+i);
        TopoSort(dfg,&chro[i]);
        fitness(dfg,&chro[i]);
        //*
        printf("\ncreate random chro %d\n",i);
        for(j=0;j<chro[i].num_of_gene;j++)
            printf("%d ",chro[i].prio[j]);
        printf("\ntopo:");
        for(j=0;j<chro[i].num_of_gene;j++)
            printf("%d ",chro[i].topo[j]);
        printf("\npower %10.4f\n",chro[i].power);  //*/
    }
    // vong lap chinh
    for(k=0;k<max_gen;k++)
    {
        //lai ghep
        srand(time(0)+k*10+1);
        for(i=0;i<(pop_size*pc/2);i++)
        {
            int randomChro1 = rand()%(pop_size);
            int randomChro2 = rand()%(pop_size);
            while(randomChro1==randomChro2)
                randomChro2 = rand()%(pop_size);
            crossOver2(&chro[a[randomChro1]],&chro[a[randomChro2]],&chro[a[pop_size+i]]);
            if(equal(&chro[a[randomChro1]],&chro[a[pop_size+i]])==1)
                mutation(&chro[a[randomChro1]],&chro[a[pop_size+i]]);
            TopoSort(dfg,&chro[a[pop_size+i]]);
            fitness(dfg,&chro[a[pop_size+i]]);
        }
        // dot bien
        srand(time(0)+k*40+1);
        for(i=0;i<(pop_size*pm);i++)
        {
            int randomChro = rand()%(3*pop_size/2);
            //printf("\nmutation chro %d", randomChro);
            mutation(&chro[a[randomChro]],&chro[a[(3*pop_size/2)+i]]);
            TopoSort(dfg,&chro[a[(3*pop_size/2)+i]]);
            fitness(dfg,&chro[a[(3*pop_size/2)+i]]);
        }
        //  sap xep
        for(i=0;i<pop_size*2;i++)
            for(j=pop_size*2-1;j>i;j--)
                if(chro[a[j-1]].power >= chro[a[j]].power)
                {
                    tmp = a[j];
                    a[j] = a[j-1];
                    a[j-1] = tmp;
                }
     //*
        printf("\nbest solution the he %d la %d :",k,a[0]);
        for(j=0;j<chro[a[0]].num_of_gene;j++)
            printf("%d ",chro[a[0]].topo[j]);  //*/
    }
    for(i=0;i<dfg->numOfNode;i++)
    {
        dfg->schedule[i] = chro[a[0]].topo[i];
        dfg->node[dfg->schedule[i]].assigned_value = i;
    }
}

void crossOver2(struct Chromosome* chro1,struct Chromosome* chro2,struct Chromosome* C)
{
    int i,j,tmp;
    int x,y; // random gene from
    struct List tmpList1,tmpList2;
    init(&tmpList1);
    init(&tmpList2);
    C->num_of_gene = chro1->num_of_gene;
    //srand(randSeed);
    x = rand()%(chro1->num_of_gene);
    y = rand()%(chro1->num_of_gene);
    while(x==y)
    {
        y = rand()%(chro1->num_of_gene);
    }
    if(x>y)
    {
        tmp = x;
        x = y;
        y = tmp;
    }
    //printf("\nx %d -- y %d",x,y);
    //------------------
    for(i=y;i>=x;i--)
        add(&tmpList1,chro1->prio[i]);
    for(i=0;i<chro2->num_of_gene;i++)
        if(contain(&tmpList1,chro2->prio[i])==0)
            add(&tmpList2,chro2->prio[i]);
    i=x;
    j=-1;
    while(tmpList1.numOfElem < chro1->num_of_gene)
    {
        if(i==0)
        {
            i = chro1->num_of_gene;
            i--;
            j++;
            if(chro1->prio[i] != tmpList2.Elem[j])
            {
                if(contain(&tmpList1,chro1->prio[i])==0)
                    add(&tmpList1,chro1->prio[i]);
                if(contain(&tmpList1,tmpList2.Elem[j])==0)
                    add(&tmpList1,tmpList2.Elem[j]);
            }
            else
                    add(&tmpList1,chro1->prio[i]);
        }
        else if(y==chro1->num_of_gene-1)
        {
            i--;
            j++;
            if(chro1->prio[i] != tmpList2.Elem[j])
            {
                if(contain(&tmpList1,chro1->prio[i])==0)
                    insert(&tmpList1,chro1->prio[i],0);
                if(contain(&tmpList1,tmpList2.Elem[j])==0)
                    insert(&tmpList1,tmpList2.Elem[j],0);
            }
            else
                insert(&tmpList1,chro1->prio[i],0);
        }
        else
        {
            i--;
            j++;
            if(chro1->prio[i] != tmpList2.Elem[j])
            {
                if(contain(&tmpList1,chro1->prio[i])==0)
                    insert(&tmpList1,chro1->prio[i],0);
                if(contain(&tmpList1,tmpList2.Elem[j])==0)
                    add(&tmpList1,tmpList2.Elem[j]);
            }
            else
                insert(&tmpList1,chro1->prio[i],0);
        }
    }
    C->num_of_gene = chro1->num_of_gene;
    for(i=0;i<C->num_of_gene;i++)
        C->prio[i] = tmpList1.Elem[i];
}
