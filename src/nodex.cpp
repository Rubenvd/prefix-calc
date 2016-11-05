#include "nodex.h"

NodeX::NodeX()
 : value(0)
{
}

void NodeX::setX(float x)
{
    value = x;
}

float NodeX::getValue()
{
    return value;
}
