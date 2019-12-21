#include "List.h"
//-----------------------------------------------
void init(struct List* list)
{
     list->numOfElem = 0;
     int i;
     for(i = 0; i < maxElem; i++ )
           list->Elem[i] = -1;
}
//------------------------------------------------
// them phan tu item vao danh sach
void add(struct List *list, int item){
       if(list->numOfElem < maxElem){
            list->Elem[list->numOfElem] = item;
            list->numOfElem++;
       }
}
//------------------------------------------------
// xoa phan tu item khoi danh sach
void del(struct List *list, int item){
    int i,j;
    for(i=0; i < list->numOfElem; i++)
        if(list->Elem[i] == item)
        {
            for(j=i; j < list->numOfElem-1; j++)
                     list->Elem[j] = list->Elem[j+1];
            list->numOfElem -- ;
            break;
        }

}
//-------------------------------------------------
// lay gia tri phan tu o vi tri index
int getElem(struct List *list, int index)
{
    if(index < list->numOfElem)
             return list->Elem[index];
}
int contain(struct List *list, int item)
{
    int i,result = 0;
    for(i=0; i < list->numOfElem; i++)
        if(list->Elem[i] == item)
            return 1;
    return 0;
}
void insert(struct List *list, int item, int index)
{
    int i;
    for(i=list->numOfElem;i>index;i--)
        list->Elem[i] = list->Elem[i-1];
    list->Elem[index] = item;
    list->numOfElem++;
}
