#ifndef __INTERPRETER_H
#define __INTERPRETER_H 1

#include <memory>
#include "ast.hpp"

class Scope {
	
};

class Interpreter : public TreeVisitor {
public:
	Interpreter();
	virtual ~Interpreter ();
	void Process(std::shared_ptr<ModuleRootNode> root);
private:

};

#endif
