#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
    int *values;
public:
    LeafNode(int LSize, InternalNode *p, BTreeNode *left,
             BTreeNode *right);
    int getCount();
    int getMinimum() const;
    LeafNode* insert(int value); // returns pointer to new Leaf if splits
    // else NULL
    void print(Queue <BTreeNode*> &queue);
    void addData(int value);
    LeafNode* split(int value); //(int value, int last); ?
}; //LeafNode class

#endif



