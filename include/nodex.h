#ifndef _NODEX
#define _NODEX

#include "nodebase.h"
#include <string>

class NodeX : public NodeBase
{
public:
    NodeX();
    float getValue() override;
    void setX(float x);
private:
    float value;
};
#endif
