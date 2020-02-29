#include "ast.hpp"

Node::~Node()
{
    
}

void Node::AddChild(std::shared_ptr<Node> child)
{
    children_.push_back(child);
}

std::vector< std::shared_ptr<Node> > Node::children()
{
    return children_;
}

void ModuleRootNode::Accept(AstVisitor* visitor)
{
    visitor->Visit(this);
}

std::string TypedNode::type()
{
    return type_;
}

void TypedNode::setType(std::string type)
{
    type_ = type;
}

ValueNode::ValueNode(std::shared_ptr<Value> value) : value_(value)
{
    type_ = value->type;
    
}

void ValueNode::Accept(AstVisitor *visitor)
{
    visitor->Visit(this);
}

std::shared_ptr<Value> ValueNode::value()
{
    return value_;
}

FunctionDefinitionNode::FunctionDefinitionNode(std::string& name)
: name_(name)
{
    
}
std::shared_ptr<Value> FunctionDefinitionNode::value()
{
    return nullptr;
}
void FunctionDefinitionNode::Accept(AstVisitor* visitor)
{
    visitor->Visit(this);
}

std::string FunctionDefinitionNode::name()
{
    return name_;
}

std::vector< std::shared_ptr<FunctionArgumentNode> > FunctionDefinitionNode::arguments()
{
    return arguments_;
}

void FunctionDefinitionNode::AddArgument(std::shared_ptr<FunctionArgumentNode> argument)
{
    arguments_.push_back(argument);
}

FunctionArgumentNode::FunctionArgumentNode(std::string& name)
: name_(name)
{
    
}

std::shared_ptr<Value> FunctionArgumentNode::value()
{
    return nullptr;
}
void FunctionArgumentNode::Accept(AstVisitor* visitor)
{
    visitor->Visit(this);
}

std::string FunctionArgumentNode::name()
{
    return name_;
}

VariableDeclarationNode::VariableDeclarationNode(std::string& name)
: name_(name)
{
    
}

std::shared_ptr<Value> VariableDeclarationNode::value()
{
    return nullptr;
}
void VariableDeclarationNode::Accept(AstVisitor* visitor)
{
    visitor->Visit(this);
}

std::string VariableDeclarationNode::name()
{
    return name_;
}

FunctionCallNode::FunctionCallNode(std::string& functionName)
: functionName_(functionName)
{
    
}
std::shared_ptr<Value> FunctionCallNode::value()
{
    return nullptr;
}

void FunctionCallNode::Accept(AstVisitor* visitor)
{
    visitor->Visit(this);
}

void FunctionReturnNode::Accept(AstVisitor* visitor)
{
    visitor->Visit(this);
}

std::shared_ptr<Value> FunctionReturnNode::value()
{
    return nullptr;
}


std::string FunctionCallNode::functionName()
{
    return functionName_;
}

VariableNode::VariableNode(std::string& name)
: name_(name)
{
    
}

void VariableNode::Accept(AstVisitor* visitor)
{
    visitor->Visit(this);
}

std::string VariableNode::name()
{
    return name_;
}
