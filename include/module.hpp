#ifndef __MODULE_H
#define __MODULE_H 1

#include <string>
#include <unordered_map>
#include <vector>
#include "nameable.hpp"
#include "symbol_table.hpp"

enum class Opcode {
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

class Type : public Nameable
{
public:
	Type()
	{
		name_ = std::string("");
	}
	explicit Type(const char* name)
	{
		name_ = name;
	}
    virtual ~Type() {}
	virtual std::string name() const
	{
		return name_;
	}
	virtual void setName(const std::string& name)
	{
		name_ = name;
	}
private:
	std::string name_;
};

struct FunctionArgument
{
	std::shared_ptr<Type> type;
	std::string name;
};

struct Function
{
	std::string name;
	std::vector<FunctionArgument> arguments;
	std::shared_ptr<Type> returnType;
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
	SymbolTable typeTable;
	std::unordered_map<std::string, Function> functionTable;
	StringTable stringTable;
	std::vector<Instruction> instructions;
	int entryPoint;
};

#endif
