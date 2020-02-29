#ifndef __PARSER_H
#define __PARSER_H 1

#include <memory>
#include <unordered_map>
#include "ast.hpp"
#include "logger.hpp"
#include "tokenizer.hpp"

class Parser
{
public:
    Parser(std::shared_ptr<Tokenizer> tokenizer);
    std::shared_ptr<ModuleRootNode> Parse();
private:
    void GetNextToken();
    void FunctionDefinitions(std::shared_ptr<Node> root);
    void FunctionDefinition(std::shared_ptr<Node> root);
    void ArgumentsList(std::shared_ptr<FunctionDefinitionNode> functionDefinitionNode);
    void Argument(std::shared_ptr<FunctionDefinitionNode> functionDefinitionNode);
    void ArgumentTrails(std::shared_ptr<FunctionDefinitionNode> functionDefinitionNode);
    void TypeSpecifier(std::shared_ptr<TypedNode> typedNode);
    void Expressions(std::shared_ptr<TypedNode> node);
    void Expression(std::shared_ptr<TypedNode> node);
    void Assignment(std::shared_ptr<Node> node);
    void VariableDeclaration(std::shared_ptr<TypedNode> node);
    void FunctionReturn(std::shared_ptr<TypedNode> node);
    void Rvalue(std::shared_ptr<Node> node);
    void PassedArguments(std::shared_ptr<FunctionCallNode> node);
    void PassedArgumentsTrails(std::shared_ptr<FunctionCallNode> node);
    Token nextToken_;
    std::shared_ptr<Tokenizer> tokenizer_;
    std::shared_ptr<Logger> logger_ = LoggerFactory::GetLogger("Parser");
};

#endif
