#ifndef _PREFIXCALC
#define _PREFIXCALC

#include <string>
#include "nodebase.h"

class PrefixCalc
{
public:
    PrefixCalc(std::string formula);
    ~PrefixCalc();
    float getValue();
private:
    NodeBase * constructNode(std::string format);
    bool isNumber(std::string);
    bool isCalculation(std::string);

    unsigned int getNextElementLength(std::string);

    NodeBase * _tree;
    unsigned int _position;
};

#endif
