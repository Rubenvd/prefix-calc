#include "nodeleaf.h"

NodeLeaf::NodeLeaf(std::string numberString)
 : value(0)
{
    unsigned int index = 0;
    bool comma = false;
    bool negative = false;
    float digits = 0;

    if(numberString[0] == '-'){
        negative = true;
        index++;
    }

    while(index < numberString.size()){
        char c = numberString[index];
        if(c >= '0' && c <= '9'){
            if(!comma){
                value = (value * 10) + c - '0';
            } else {
                digits = (digits * 10) + c - '0';
            }
        }else if(c == '.'){
            if(comma){
                throw std::string("Too many commas!");
            }
            comma = true;
        }else{
            throw std::string("Don't even know what's happening");
        }
        index++;
    }

    if(comma){
        while(digits > 1){
            digits = digits / 10.0;
        }
        value += digits;
    }

    if(negative){
        value = -value;
    }
}

float NodeLeaf::getValue()
{
    return value;
}
