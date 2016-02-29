#include "parser.hpp"

Parser::Parser(std::shared_ptr<Tokenizer> tokenizer)
	: tokenizer_(tokenizer)
{

}


std::shared_ptr<ModuleRootNode> Parser::Parse()
{
	auto root = std::shared_ptr<ModuleRootNode>(new ModuleRootNode());
	FunctionDefinitions(root);
	// TODO: check leftovers
	return root;
}

void Parser::FunctionDefinitions(std::shared_ptr<Node> root)
{
	GetNextToken();
	if (nextToken_.type == EPSILON) {
		return;
	}
	FunctionDefinition(root);
	FunctionDefinitions(root);
	GetNextToken();
}

void Parser::FunctionDefinition(std::shared_ptr<Node> root)
{
	if (nextToken_.type != FN) {
		throw "FN expected";
	}
	GetNextToken();
	if (nextToken_.type != IDENTIFIER) {
		throw "IDENTIFIER expected";
	}
	auto functionNode =
		std::make_shared<FunctionDefinitionNode>(nextToken_.value);
	GetNextToken();
	if (nextToken_.type != L_BRACE) {
		throw "L_BRACE expected";
	}
	GetNextToken();
	ArgumentsList(functionNode);
	if (nextToken_.type != R_BRACE) {
		throw "R_BRACE expected";
	}
	TypeSpecifier(functionNode);
	GetNextToken();
	if (nextToken_.type != L_CURLY_BRACE) {
		throw "L_CURLY_BRACE expected";
	}
	Expressions(functionNode);
	if (nextToken_.type != R_CURLY_BRACE) {
		throw "R_CURLY_BRACE expected";
	}
	root->AddChild(functionNode);
}

void Parser::ArgumentsList(std::shared_ptr<FunctionDefinitionNode> functionDefinitionNode)
{
	if (nextToken_.type == R_BRACE) {
		return;
	}
	Argument(functionDefinitionNode);
	ArgumentTrails(functionDefinitionNode);
}

void Parser::Argument(std::shared_ptr<FunctionDefinitionNode> functionDefinitionNode)
{
	if (nextToken_.type != IDENTIFIER) {
		throw "IDENTIFIER expected for argument type";
	}
	auto argumentNode = std::make_shared<FunctionArgumentNode>(nextToken_.value);
	TypeSpecifier(argumentNode);
	functionDefinitionNode->AddChild(argumentNode);
}

void Parser::ArgumentTrails(std::shared_ptr<FunctionDefinitionNode> functionDefinitionNode)
{
	GetNextToken();
	if (nextToken_.type == R_BRACE) {
		return;
	}
	if (nextToken_.type != COMMA) {
		throw "COMMA expected, but we got " + nextToken_.value;
	}
	GetNextToken();
	ArgumentsList(functionDefinitionNode);
}

void Parser::TypeSpecifier(std::shared_ptr<TypedNode> typedNode)
{
	GetNextToken();
	if (nextToken_.type != COLON) {
		throw "COLON expected for type specifier";
	}
	GetNextToken();
	if (nextToken_.type != IDENTIFIER) {
		throw "IDENTIFIER expected for type name";
	}
	typedNode->setType(nextToken_.value);
}

void Parser::Expressions(std::shared_ptr<TypedNode> node)
{
		GetNextToken();
		while(nextToken_.type != R_CURLY_BRACE) {
			Expression(node);
			GetNextToken();
		}
}

void Parser::Expression(std::shared_ptr<TypedNode> node)
{
	std::shared_ptr<FunctionCallNode> functionCallNode;
	std::shared_ptr<VariableNode> variableNode;
	std::string name;
	switch (nextToken_.type) {
		case LET:
		VariableDeclaration(node);
		break;

		case IDENTIFIER:
		name = nextToken_.value;
		GetNextToken();
		if (nextToken_.type == L_BRACE) {
			functionCallNode = std::make_shared<FunctionCallNode>(name);
			PassedArguments(functionCallNode);
			node->AddChild(functionCallNode);
			GetNextToken();
		} else {
			variableNode = std::make_shared<VariableNode>(name);
			node->AddChild(variableNode);
		}
		break;
	}
	if (nextToken_.type != SEMICOLON) {
		std::cout << nextToken_.value << std::endl;
		throw "SEMICOLON expected in the end of expression";
	}
}

void Parser::VariableDeclaration(std::shared_ptr<TypedNode> node)
{
	GetNextToken();
	if (nextToken_.type != IDENTIFIER) {
		throw "IDENTIFIER expected for variable declaration";
	}
	auto variableDeclarationNode = std::make_shared<VariableDeclarationNode>(nextToken_.value);
	TypeSpecifier(variableDeclarationNode);
	Assignment(variableDeclarationNode);
	node->AddChild(variableDeclarationNode);
}

void Parser::Assignment(std::shared_ptr<Node> node)
{
	GetNextToken();
	if (nextToken_.type != EQ) {
		throw "EQ expected for assignment";
	}
	GetNextToken();
	Rvalue(node);
}

void Parser::Rvalue(std::shared_ptr<Node> node)
{
	std::shared_ptr<FunctionCallNode> functionCallNode;
	std::shared_ptr<Node> child;
	std::shared_ptr<Value> value = std::make_shared<Value>();
	std::string name;
	switch (nextToken_.type) {
		case STRING_LITERAL:
		value->type = "String";
		value->content = nextToken_.value;
		child = std::make_shared<ValueNode>(value);
		GetNextToken();
		break;

		case INTEGER:
		value->type = "Int";
		value->content = nextToken_.value;
		child = std::make_shared<ValueNode>(value);
		GetNextToken();
		break;

		case IDENTIFIER:
		name = nextToken_.value;
		GetNextToken();
		if (nextToken_.type == L_BRACE) {
			functionCallNode = std::make_shared<FunctionCallNode>(name);
			PassedArguments(functionCallNode);
			child = functionCallNode;
		} else {
			child = std::make_shared<VariableNode>(name);
		}
		break;

		default:
		throw "STRING_LITERAL or INTEGER expected for rvalue";
	}
	node->AddChild(child);
}

void Parser::PassedArguments(std::shared_ptr<FunctionCallNode> node)
{
	GetNextToken();
	while (nextToken_.type != R_BRACE) {
		Rvalue(node);
		PassedArgumentsTrails(node);
	}
}

void Parser::PassedArgumentsTrails(std::shared_ptr<FunctionCallNode> node)
{
	if (nextToken_.type == R_BRACE) {
		return;
	}
	if (nextToken_.type != COMMA) {
		throw "COMMA expected for passed arguments";
	}
	PassedArguments(node);
}

void Parser::GetNextToken()
{
	nextToken_ = tokenizer_->GetNextToken();
	logger_->Debug(nextToken_.ToString());
}
