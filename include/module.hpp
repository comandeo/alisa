#ifndef __MODULE_H
#define __MODULE_H 1

#include <string>
#include <unordered_map>
#include <vector>

enum Opcode {
	HLT,
	PUSHI,
	JUMP,
	RETURN,
	PRINT
};

struct Instruction
{
	Opcode opcode;
	int arg1 = 0, arg2 = 0, arg3 = 0;
	std::string ToString();
};

struct Type
{
	std::string name;
};

struct FunctionArgument
{
	Type type;
	std::string name;
};

struct Function
{
	std::string name;
	std::vector<FunctionArgument> arguments;
	Type returnType;
	unsigned long offset;
};

class StringTable
{
public:
	int Add(std::string& string);

	int GetStringIndex(std::string& string);

	std::string& GetStringByIndex(int index);
private:
	std::vector<std::string> strings_;
};

struct Module
{
	std::unordered_map<std::string, Type> typeTable;
	std::unordered_map<std::string, Function> functionTable;
	StringTable stringTable;
	std::vector<Instruction> instructions;
	int entryPoint;
};

#endif
