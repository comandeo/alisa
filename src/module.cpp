#include <iostream>
#include "module.hpp"

std::string Instruction::ToString()
{
    std::string result;
    switch (opcode) {
        case Opcode::HLT:
            result = "HLT";
            break;
        case Opcode::PUSHI:
            result = "PUSHI ";
            result.append(std::to_string(arg1));
            break;
        case Opcode::JUMP:
            result ="JUMP";
            break;
        case Opcode::RETURN:
            result = "RETURN";
            break;
        case Opcode::PRINT:
            result = "PRINT";
            break;
    }
    return result;
}

int StringTable::Add(std::string& string)
{
    strings_.push_back(string);
    return strings_.size() - 1;
}

int StringTable::GetStringIndex(std::string& string)
{
    for (int i = 0; i < strings_.size(); i++) {
        if (strings_[i] == string) {
            return i;
        }
    }
    return -1;
}

std::string& StringTable::GetStringByIndex(int index)
{
    return strings_[index];
}
