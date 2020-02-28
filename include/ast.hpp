#ifndef __AST_H
#define __AST_H 1

#include <memory>
#include <string>
#include <vector>

struct Value {
    std::string type;
    std::string content;
};

class ModuleRootNode;
class FunctionDefinitionNode;
class FunctionArgumentNode;
class VariableDeclarationNode;
class FunctionReturnNode;
class ValueNode;
class FunctionCallNode;
class VariableNode;

class AstVisitor
{
public:
    virtual void Visit(ModuleRootNode* node) = 0;
    virtual void Visit(FunctionDefinitionNode* node) = 0;
    virtual void Visit(FunctionArgumentNode* node) = 0;
    virtual void Visit(VariableDeclarationNode* node) = 0;
    virtual void Visit(FunctionReturnNode* node) = 0;
    virtual void Visit(ValueNode* node) = 0;
    virtual void Visit(FunctionCallNode* node) = 0;
    virtual void Visit(VariableNode* node) = 0;
};

class Node
{
public:
    virtual ~Node();
    virtual void AddChild(std::shared_ptr<Node> child);
    virtual std::vector< std::shared_ptr<Node> > children();
    virtual void Accept(AstVisitor* visitor) = 0;
protected:
    std::vector< std::shared_ptr<Node> > children_;
};

class ModuleRootNode : public Node
{
public:
    virtual void Accept(AstVisitor* visitor);
};

class TypedNode : public Node
{
public:
    virtual std::string type();
    virtual void setType(std::string type);
protected:
    std::string type_;
};

class ExpressionNode : public TypedNode
{
public:
    virtual std::shared_ptr<Value> value() = 0;
};

class ValueNode : public ExpressionNode
{
public:
    ValueNode(std::shared_ptr<Value> value);
    virtual void Accept(AstVisitor* visitor);
    virtual std::shared_ptr<Value> value();
private:
    std::shared_ptr<Value> value_;
};

class FunctionDefinitionNode : public ExpressionNode
{
public:
    FunctionDefinitionNode(std::string& name);
    virtual std::shared_ptr<Value> value();
    virtual void Accept(AstVisitor* visitor);
    std::string name();
    std::vector< std::shared_ptr<FunctionArgumentNode> > arguments();
    void AddArgument(std::shared_ptr<FunctionArgumentNode> argument);
private:
    std::string name_;
    std::vector< std::shared_ptr<FunctionArgumentNode> > arguments_;
};

class FunctionArgumentNode : public ExpressionNode
{
public:
    FunctionArgumentNode(std::string& name);
    virtual std::shared_ptr<Value> value();
    virtual void Accept(AstVisitor* visitor);
    std::string name();
private:
    std::string name_;
};

class VariableDeclarationNode : public ExpressionNode
{
public:
    VariableDeclarationNode(std::string& name);
    virtual std::shared_ptr<Value> value();
    virtual void Accept(AstVisitor* visitor);
    std::string name();
private:
    std::string name_;
};

class FunctionReturnNode : public ExpressionNode
{
public:
    virtual std::shared_ptr<Value> value();
    virtual void Accept(AstVisitor* visitor);
};

class FunctionCallNode : public ExpressionNode
{
public:
    FunctionCallNode(std::string& functionName);
    virtual std::shared_ptr<Value> value();
    virtual void Accept(AstVisitor* visitor);
    std::string functionName();
private:
    std::string functionName_;
};

class VariableNode : public Node
{
public:
    VariableNode(std::string& name);
    virtual void Accept(AstVisitor* visitor);
    std::string name();
private:
    std::string name_;
};
#endif
