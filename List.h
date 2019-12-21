
#ifndef _LIST_H_
#define _LIST_H_

#define maxElem 60
//-----------------------------------------------
struct List{
       int numOfElem;
       int Elem[maxElem];
};
void init(struct List* list);
void add(struct List *list, int item);
void del(struct List *list, int item);
int getElem(struct List *list, int index);
int contain(struct List *list, int item);
void insert(struct List *list, int item, int index);
#endif
