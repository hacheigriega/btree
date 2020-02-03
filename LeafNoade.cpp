#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
                   BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
    values = new int[LSize];
}  // LeafNode()


int LeafNode::getMinimum()const
{
    if(count > 0)  // should always be the case
        return values[0];
    else
        return 0;
} // LeafNode::getMinimum()




LeafNode* LeafNode::insert(int value)
{
    int pos1, pos2;
    int first, last;
    int temp;
    
    // if count is smaller than leafSize, add
    if (count < leafSize)
    {
        for(pos1 = 0; pos1 < count-1; pos1++)
        {
            if(value < values[pos1])
            {
                temp = values[pos1];
                values[pos1] = value;
                count++;
                
                for(pos2 = count-1; pos2 > pos1; pos2--)
                    values[pos2+1] = values[pos2];
                // shift up all elements
                
                values[pos2] = temp; // everything in its right place
                
                if(parent)
                    parent->setKeys(this);
                
                return NULL;
            }
        }
    }
    
    // find first and last
    if(value < values[0])
    {
        first = value;
    }
    
    for(pos1 = 0; pos1 < count-1; pos1++)
    {
        if(value < values[pos1])
        {
            temp = values[pos1];
            values[pos1] = value; // do not increment count
            
            for(pos2 = count-1; pos2 > pos1; pos2--)
                values[pos2+1] = values[pos2];
            // shift up all elements
            
            values[pos2] = temp; // everything in its right place
            last = values[count];
        }
    }
    
    // give left, give right, else split
    if(leftSibling->getCount() < leafSize)
    {
        leftSibling->insert(last);
        
        for(pos1 = 0; pos1 < count-1; pos1++)
        {
            values[pos1] = values[pos1+1];
        } // shift down all elements
        
        values[count-1] = last;
        if(parent)
            parent->setKeys(this);
        
        return NULL;
        // add to left
    } else if(rightSibling->getCount() < leafSize)
    {
        rightSibling->insert(last);
        
        if(parent)
            parent->setKeys(this);
        
        return NULL;
        // add to right
    } else {
        return this->split(value);
        // left and right both full. split.
    }
    
    return NULL; // to avoid warnings for now.
}  // LeafNode::insert()


void LeafNode::print(Queue <BTreeNode*> &queue)
{
    cout << "Leaf: ";
    for (int i = 0; i < count; i++)
        cout << values[i] << ' ';
    cout << endl;
} // LeafNode::print()


LeafNode* LeafNode::split(int value) //(int value, int last)?
{
    int i, pos = 0;
    LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);
    
    if(rightSibling)
        rightSibling->setLeftSibling(ptr);
    
    rightSibling = ptr;
    
    
    for(i = (leafSize+1) / 2; i < leafSize; i++)
    {
        ptr->values[pos] = values[i];
        ptr->count++;
        pos++;
    }
    
    ptr->values[i+1] = value;
    ptr->count++;
    
    if(parent) 
        parent->setKeys(this); //check?
    
    return ptr;
}  


int LeafNode::getCount() 
{
    return count;
}

