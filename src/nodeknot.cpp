#include "nodeknot.h"
#include <string>

NodeKnot::NodeKnot(char operation)
{
    switch(operation){
    case '/':
        _calculation = [](float a, float b){
            if(b == 0){
                throw std::string("Tried to divide by zero");
            }
            return a/b;
        };
        break;
    case '*':
        _calculation = [](float a, float b){ return a*b; };
        break;
    case '+':
        _calculation = [](float a, float b){ return a+b; };
        break;
    case '-':
        _calculation = [](float a, float b){ return a-b; };
        break;
    default:
        break;
    }
}

void NodeKnot::setLeft(NodeBase * left)
{
    _left = left;
}

void NodeKnot::setRight(NodeBase * right)
{
    _right = right;
}

float NodeKnot::getValue()
{
    return _calculation(_left->getValue(), _right->getValue());
}
