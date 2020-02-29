#ifndef __VM_H
#define __VM_H 1

#include <stack>
#include "module.hpp"


class VM
{
public:
    void Process(Module& module);
private:
    int ip_;
    std::stack<int> stack_;
    StringTable stringTable_;
};

#endif
