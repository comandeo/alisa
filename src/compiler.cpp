#include <iostream>
#include "compiler.hpp"


void Compiler::Visit(ModuleRootNode* node)
{
	module_ = Module();
	buildStandardLibrary();
	for (auto child : node->children()) {
		child->Accept(this);
	}
	auto main = module_.functionTable.find("main");
	if (main == module_.functionTable.end()) {
		throw "No function 'main' in module";
	}
	module_.entryPoint = module_.instructions.size();
	Instruction saveReturnAddress;
	saveReturnAddress.opcode = PUSHI;
	saveReturnAddress.arg1 = module_.instructions.size() + 3;
	module_.instructions.push_back(saveReturnAddress);
	Instruction pushJmpAddress;
	pushJmpAddress.opcode = PUSHI;
	pushJmpAddress.arg1 = main->second.offset;
	module_.instructions.push_back(pushJmpAddress);
	Instruction call;
	call.opcode = JUMP;
	module_.instructions.push_back(call);
	Instruction halt;
	halt.opcode = HLT;
	module_.instructions.push_back(halt);
}

void Compiler::Visit(FunctionDefinitionNode* node)
{
	Function function;
	function.name = node->name();
	function.offset = module_.instructions.size();
	std::cout << "Function " << function.name << " with offset " << function.offset << std::endl;
	auto returnType = module_.typeTable.find(node->type());
	if (returnType == module_.typeTable.end()) {
		throw "Unknown function return type";
	}
	function.returnType = returnType->second;
	for (auto argumentNode : node->arguments()) {
		auto type = module_.typeTable.find(node->type());
		if (type == module_.typeTable.end()) {
			throw "Unknown argument type";
		}
	}
	for (auto child : node->children()) {
		child->Accept(this);
	}
	Instruction ret;
	ret.opcode = RETURN;
	module_.instructions.push_back(ret);
	module_.functionTable[function.name] = function;
}

void Compiler::Visit(FunctionArgumentNode* node) {}
void Compiler::Visit(VariableDeclarationNode* node) {}
void Compiler::Visit(ValueNode* node)
{
	std::cout << "Value node with type " << node->type() << std::endl;
	if (module_.typeTable.find(node->type()) == module_.typeTable.end()) {
		throw "Unknown value type";
	}
	Type type = module_.typeTable[node->type()];
	if (type.name == "String") {
		int stringIndex = module_.stringTable.GetStringIndex(node->value()->content);
		if (stringIndex == -1) {
			stringIndex = module_.stringTable.Add(node->value()->content);
		}
		Instruction saveStringIndex;
		saveStringIndex.opcode = PUSHI;
		saveStringIndex.arg1 = stringIndex;
		module_.instructions.push_back(saveStringIndex);
	}
}

void Compiler::Visit(FunctionCallNode* node)
{
	std::cout << "Call function " << node->functionName() << std::endl;
	auto calledFunction = module_.functionTable.find(node->functionName());
	if (calledFunction == module_.functionTable.end()) {
		throw "Calling unknown function";
	}
	Instruction saveReturnAddress;
	saveReturnAddress.opcode = PUSHI;
	saveReturnAddress.arg1 = module_.instructions.size() + 4;
	module_.instructions.push_back(saveReturnAddress);
	for (auto argument : node->children()) {
		argument->Accept(this);
	}
	Instruction pushJmpAddress;
	pushJmpAddress.opcode = PUSHI;
	pushJmpAddress.arg1 = calledFunction->second.offset;
	module_.instructions.push_back(pushJmpAddress);
	Instruction call;
	call.opcode = JUMP;
	module_.instructions.push_back(call);
}

void Compiler::Visit(VariableNode* node) {}

Module& Compiler::module()
{
	return module_;
}

void Compiler::buildStandardLibrary()
{
	module_.typeTable["Void"] = Type();
	module_.typeTable["Void"].name = "Void";
	module_.typeTable["Int"] = Type();
	module_.typeTable["Int"].name = "Int";
	module_.typeTable["String"] = Type();
	module_.typeTable["String"].name = "String";

	Function print;
	print.name = "print";
	print.returnType = module_.typeTable["Void"];
	print.offset = 0;
	FunctionArgument argument;
	argument.type = module_.typeTable["String"];
	argument.name = "str";
	print.arguments.push_back(argument);
	module_.functionTable[print.name] = print;
	Instruction prt;
	prt.opcode = PRINT;
	module_.instructions.push_back(prt);
	Instruction ret;
	ret.opcode = RETURN;
	module_.instructions.push_back(ret);
}
