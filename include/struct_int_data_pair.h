#ifndef STRUCT_INT_DATA_PAIR_H
#define STRUCT_INT_DATA_PAIR_H

typedef struct pairNode{
    int distance;
    int nodeIndex;
    pairNode(int dist, int index) : distance(dist), nodeIndex(index) {}

} pairNode;

#endif // STRUCT_INT_DATA_PAIR_H
