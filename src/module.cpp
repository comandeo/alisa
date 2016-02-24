#include <iostream>
#include "module.hpp"

void Instruction::Trace()
{
	switch (opcode) {
	case HLT:
		std::cout << "HLT";
		break;
	case PUSHI:
		std::cout << "PUSHI " << arg1;
		break;
	case JUMP:
		std::cout << "JUMP";
		break;
	case RETURN:
		std::cout << "RETURN";
		break;
	case PRINT:
		std::cout << "PRINT";
		break;
	}
	std::cout << std::endl;
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

Module::Module()
{
	typeTable["Void"] = Type();
	typeTable["Void"].name = "Void";
	typeTable["Int"] = Type();
	typeTable["Int"].name = "Int";
	typeTable["String"] = Type();
	typeTable["String"].name = "String";

	Function print;
	print.name = "print";
	print.returnType = typeTable["Void"];
	print.offset = 0;
	FunctionArgument argument;
	argument.type = typeTable["String"];
	argument.name = "str";
	print.arguments.push_back(argument);
	functionTable[print.name] = print;
	Instruction prt;
	prt.opcode = PRINT;
	instructions.push_back(prt);
	Instruction ret;
	ret.opcode = RETURN;
	instructions.push_back(ret);
}
