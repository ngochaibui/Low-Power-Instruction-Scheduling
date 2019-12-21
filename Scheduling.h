#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_
double PDT[12][12];
// ham nay dung cho ASAP va ALAP
int allNodesScheduled(struct List list, struct DFG dfg, char* schedule);

// ham nay dung cho thuat toan lap lich chinh FDS
int allScheduled(struct DFG dfg);
void ASAP(struct DFG *dfg);
void ALAP(struct DFG *dfg);
void ListSchedule(struct DFG *dfg);
void inputPDT();
#endif
