#include <iostream>
#include <unordered_map>
#include <vector>
#include "compiler.hpp"

enum Opcode {
	HLT,
	PUSHI,
	CALL,
	PRINT
};

struct Instruction
{
	Opcode opcode;
	int arg1, arg2, arg3;

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

struct Module
{
	std::unordered_map<std::string, Type> typeTable;
	std::unordered_map<std::string, Function> functionTable;
	unsigned long ip = 0;
	std::vector<Instruction> instructions;
	Module()
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
		FunctionArgument argument;
		argument.type = typeTable["String"];
		argument.name = "str";
		print.arguments.push_back(argument);
		functionTable[print.name] = print;

	}
};

void Compiler::Visit(ModuleRootNode* node)
{
	module_ = new Module();
	for (auto child : node->children()) {
		child->Accept(this);
	}
}

void Compiler::Visit(FunctionDefinitionNode* node)
{
	std::cout << "Function " << node->name() << std::endl;
	//auto existingFunction = module_->functionTable.find(node->name());
	//if (existingFunction == module_->functionTable.end()) {
		//throw "Function already exists";
	//}
	Function function;
	function.name = node->name();
	auto returnType = module_->typeTable.find(node->type());
	if (returnType == module_->typeTable.end()) {
			throw "Unknown function return type";
	}
	function.returnType = returnType->second;
	for (auto argumentNode : node->arguments()) {
		auto type = module_->typeTable.find(node->type());
		if (type == module_->typeTable.end()) {
			throw "Unknown argument type";
		}
	}
	for (auto child : node->children()) {
		child->Accept(this);
	}
	module_->functionTable[function.name] = function;
}

void Compiler::Visit(FunctionArgumentNode* node) {}
void Compiler::Visit(VariableDeclarationNode* node) {}
void Compiler::Visit(ValueNode* node) {}

void Compiler::Visit(FunctionCallNode* node) {
	std::cout << "Call function " << node->functionName() << std::endl;
	auto calledFunction = module_->functionTable.find(node->functionName());
	if (calledFunction == module_->functionTable.end()) {
		throw "Calling unknown function";
	}
	Instruction saveReturnAddress;
	saveReturnAddress.opcode = PUSHI;
	saveReturnAddress.arg1 = module_->ip + 2;
	module_->instructions.push_back(saveReturnAddress);
	module_->ip++;
	Instruction call;
	call.opcode = CALL;
	call.arg1 = calledFunction->second.offset;
	module_->instructions.push_back(call);
	Function function;
}

void Compiler::Visit(VariableNode* node) {}
