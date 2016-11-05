#ifndef _PREFIXCALC
#define _PREFIXCALC

#include <string>
#include "nodebase.h"
#include "nodex.h"

class PrefixCalc
{
public:
    PrefixCalc(std::string formula);
    ~PrefixCalc();
    float getValue();
    float getValueIfXIs(float);
private:
    NodeBase * constructNode(std::string format);
    unsigned int getNextElementLength(std::string);
    bool isNumber(std::string);
    bool isCalculation(std::string);
    bool isX(std::string);

    NodeBase * _tree;
    NodeX * _xNode;
    unsigned int _position;
};

#endif
