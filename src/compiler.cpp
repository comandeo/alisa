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
	saveReturnAddress.opcode = Opcode::PUSHI;
	saveReturnAddress.arg1 = module_.instructions.size() + 3;
	module_.instructions.push_back(saveReturnAddress);
	Instruction pushJmpAddress;
	pushJmpAddress.opcode = Opcode::PUSHI;
	pushJmpAddress.arg1 = main->second.offset;
	module_.instructions.push_back(pushJmpAddress);
	Instruction call;
	call.opcode = Opcode::JUMP;
	module_.instructions.push_back(call);
	Instruction halt;
	halt.opcode = Opcode::HLT;
	module_.instructions.push_back(halt);
}

void Compiler::Visit(FunctionDefinitionNode* node)
{
	Function function;
	function.name = node->name();
	function.offset = module_.instructions.size();
	std::cout << "Function " << function.name << " with offset " << function.offset << std::endl;
	auto returnType = module_.typeTable.Get(node->type());
	if (returnType == nullptr) {
		throw "Unknown function return type";
	}
	function.returnType = std::dynamic_pointer_cast<Type>(returnType);
	for (auto argumentNode : node->arguments()) {
		auto type = module_.typeTable.Get(node->type());
		if (type == nullptr) {
			throw "Unknown argument type";
		}
	}
	for (auto child : node->children()) {
		child->Accept(this);
        if(std::dynamic_pointer_cast<FunctionReturnNode>(child)) {
            Instruction ret;
            ret.opcode = Opcode::RETURN;
            module_.instructions.push_back(ret);
            module_.functionTable[function.name] = function;
            return;
        }
	}
	Instruction jmp;
	jmp.opcode = Opcode::JUMP;
	module_.instructions.push_back(jmp);
	module_.functionTable[function.name] = function;
}

void Compiler::Visit(FunctionArgumentNode* node) {}
void Compiler::Visit(VariableDeclarationNode* node) {}

void Compiler::Visit(FunctionReturnNode* node)
{
    for (auto child : node->children()) {
        child->Accept(this);
    }
}
void Compiler::Visit(ValueNode* node)
{
	std::cout << "Value node with type " << node->type() << std::endl;
	if (module_.typeTable.Get(node->type()) == nullptr) {
		throw "Unknown value type";
	}
	auto type = module_.typeTable.Get(node->type());
	if (type->name() == "String") {
		int stringIndex = module_.stringTable.GetStringIndex(node->value()->content);
		if (stringIndex == -1) {
			stringIndex = module_.stringTable.Add(node->value()->content);
		}
		Instruction saveStringIndex;
		saveStringIndex.opcode = Opcode::PUSHI;
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
	saveReturnAddress.opcode = Opcode::PUSHI;
	module_.instructions.push_back(saveReturnAddress);
    auto returnAddressIdx = module_.instructions.size() - 1;
	for (auto argument : node->children()) {
		argument->Accept(this);
	}
	Instruction pushJmpAddress;
	pushJmpAddress.opcode = Opcode::PUSHI;
	pushJmpAddress.arg1 = calledFunction->second.offset;
	module_.instructions.push_back(pushJmpAddress);
	Instruction call;
	call.opcode = Opcode::JUMP;
	module_.instructions.push_back(call);
    saveReturnAddress.arg1 = module_.instructions.size();
    module_.instructions[returnAddressIdx] = saveReturnAddress;
}

void Compiler::Visit(VariableNode* node) {}

Module& Compiler::module()
{
	return module_;
}

void Compiler::buildStandardLibrary()
{
	module_.typeTable.Put(std::make_shared<Type>("Void"));
	module_.typeTable.Put(std::make_shared<Type>("Int"));
	module_.typeTable.Put(std::make_shared<Type>("String"));

	Function print;
	print.name = "print";
	print.returnType = std::dynamic_pointer_cast<Type>(module_.typeTable.Get("Void"));
	print.offset = 0;
	FunctionArgument argument;
	argument.type = std::dynamic_pointer_cast<Type>(module_.typeTable.Get("String"));
	argument.name = "str";
	print.arguments.push_back(argument);
	module_.functionTable[print.name] = print;
	Instruction prt;
	prt.opcode = Opcode::PRINT;
	module_.instructions.push_back(prt);
	Instruction jmp;
	jmp.opcode = Opcode::JUMP;
	module_.instructions.push_back(jmp);
}
