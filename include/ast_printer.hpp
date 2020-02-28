#ifndef __AST_PRINTER_H
#define __AST_PRINTER_H 1

#include <iostream>
#include "ast.hpp"

class AstPrinter : public AstVisitor
{
private:
	int level_ = 0;
	void PrintLeadingSpaces()
	{
		for (auto i = 0; i < level_; i++) {
			std::cout << " ";
		}
	}
public:
	virtual void Visit(ModuleRootNode* node)
	{
		PrintLeadingSpaces();
		std::cout << "ModuleRootNode" << std::endl;
		level_++;
		for (auto child : node->children()) {
			child->Accept(this);
		}
		level_--;
	}
	virtual void Visit(FunctionDefinitionNode* node)
	{
		PrintLeadingSpaces();
		std::cout
			<< "FunctionDefinitionNode"
			<< ": function name: " << node->name()
			<< "; return type " << node->type()
			<< std::endl;
		level_++;
		for (const auto child : node->arguments()) {
			child->Accept(this);
		}
		for (const auto child : node->children()) {
			child->Accept(this);
		}
		level_--;
	}

	virtual void Visit(FunctionArgumentNode* node)
	{
		PrintLeadingSpaces();
		std::cout
		<< "FunctionArgumentNode"
		<< ": argument name: " << node->name()
		<< "; type " << node->type()
		<< std::endl;
		level_++;
		for (const auto child : node->children()) {
			child->Accept(this);
		}
		level_--;
	}

	virtual void Visit(VariableDeclarationNode* node)
	{
		PrintLeadingSpaces();
		std::cout
		<< "VariableDeclarationNode"
		<< ": variable name: " << node->name()
		<< "; type " << node->type()
		<< std::endl;
		level_++;
		for (const auto child : node->children()) {
			child->Accept(this);
		}
		level_--;
	}
    
    virtual void Visit(FunctionReturnNode* node)
    {
        PrintLeadingSpaces();
        std::cout
        << "FunctionReturnNode"
        << std::endl;
        level_++;
        for (const auto child : node->children()) {
            child->Accept(this);
        }
        level_--;
    }

	virtual void Visit(ValueNode* node)
	{
		PrintLeadingSpaces();
		std::cout
		<< "ValueNode"
		<< ": content: " << node->value()->content
		// << "; type " << node->type().name
		<< std::endl;
		level_++;
		for (const auto child : node->children()) {
			child->Accept(this);
		}
		level_--;
	}

	virtual void Visit(FunctionCallNode* node)
	{
		PrintLeadingSpaces();
		std::cout
		<< "FunctionCallNode"
		<< ": function name: " << node->functionName()
		// << "; type " << node->type().name
		<< std::endl;
		level_++;
		for (const auto child : node->children()) {
			child->Accept(this);
		}
		level_--;
	}

	virtual void Visit(VariableNode* node)
	{
		PrintLeadingSpaces();
		std::cout
		<< "VariableNode"
		<< ": variable name: " << node->name()
		// << "; type " << node->type().name
		<< std::endl;
		level_++;
		for (const auto child : node->children()) {
			child->Accept(this);
		}
		level_--;
	}
};

#endif
