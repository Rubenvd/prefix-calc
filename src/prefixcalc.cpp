#include "prefixcalc.h"
#include "nodeleaf.h"
#include "nodeknot.h"
#include "nodex.h"
#include <iostream>

PrefixCalc::PrefixCalc(std::string formula)
    : _xNode(nullptr), _position(0)
{
    _tree = constructNode(formula);
}

PrefixCalc::~PrefixCalc()
{

}

float PrefixCalc::getValue()
{
    return _tree->getValue();
}

bool PrefixCalc::isNumber(std::string substr)
{
    for(unsigned int i = 0; i < substr.size(); i++){
        char c = substr[i];
        if((c < '0' || c > '9') && c != '.' && c != '-'){
            return false;
        }
    }
    return true;
}

bool PrefixCalc::isCalculation(std::string calculation){
    if(calculation.length() != 1){
        return false;
    }

    switch (calculation[0]){
    case '/':
    case '*':
    case '+':
    case '-':
        return true;
    default:
        return false;
    }
}

bool PrefixCalc::isX(std::string x){
    return x == "X";
}

float PrefixCalc::getValueIfXIs(float val)
{
    _xNode->setX(val);
    return _tree->getValue();
}

unsigned int PrefixCalc::getNextElementLength(std::string format)
{
    unsigned int elementLength = 0;

    while((_position + elementLength < format.length()) && format[_position + elementLength] != ' '){
        elementLength++;
    }

    return elementLength;
}

NodeBase* PrefixCalc::constructNode(std::string format)
{
    unsigned int elementLen = getNextElementLength(format);

    if(elementLen == 0){
        throw std::string("Not a correct calculation");
    }

    std::string nextElement(format.substr(_position, elementLen));
    _position += elementLen + 1;
    if(isCalculation(nextElement)){
        NodeKnot * knot = new NodeKnot(nextElement[0]);
        knot->setLeft(constructNode(format));
        knot->setRight(constructNode(format));
        return knot;
    }else if(isNumber(nextElement)){
        return new NodeLeaf(nextElement);
    }else if(isX(nextElement)){
        if(_xNode != nullptr){
            throw std::string("Too many X's!");
        }
        _xNode = new NodeX();
        return _xNode;
    }else{
        throw std::string("Incorrect string was given");
    }
    return nullptr;
}
