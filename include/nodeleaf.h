#ifndef _NODELEAF
#define _NODELEAF

#include "nodebase.h"
#include <string>

class NodeLeaf : public NodeBase
{
public:
    NodeLeaf(std::string);
    float getValue() override;
private:
    float value;
};
#endif
