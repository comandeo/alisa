#ifndef __COMPILER_H
#define __COMPILER_H 1

#include <memory>
#include "ast.hpp"

class Module;
struct Function;

class Compiler : public AstVisitor
{
public:
	virtual void Visit(ModuleRootNode* node);
	virtual void Visit(FunctionDefinitionNode* node);
	virtual void Visit(FunctionArgumentNode* node);
	virtual void Visit(VariableDeclarationNode* node);
	virtual void Visit(ValueNode* node);
	virtual void Visit(FunctionCallNode* node);
	virtual void Visit(VariableNode* node);
private:
	Module* module_;
};

#endif
