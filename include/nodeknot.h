#ifndef _NODEKNOT
#define _NODEKNOT

#include "nodebase.h"

class NodeKnot : public NodeBase
{
public:
    NodeKnot(char operation);
    void setRight(NodeBase * right);
    void setLeft(NodeBase * left);

    float getValue() override;
private:
    NodeBase * _right;
    NodeBase * _left;
    float (*_calculation)(float,float);
};

#endif
