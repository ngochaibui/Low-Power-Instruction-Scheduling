#ifndef _GENETIC_H_
#define _GENETIC_H_
#define MAX_NODES 60
struct Chromosome{
    int num_of_gene;
    int prio[MAX_NODES];
    int topo[MAX_NODES];
    double power;
};
#endif
