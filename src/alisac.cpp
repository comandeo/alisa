#include <fstream>
#include <iostream>
#include <memory>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "ast_printer.hpp"
#include "compiler.hpp"
#include "module.hpp"
#include "logger.hpp"
#include "module_serializer.hpp"

int main(int argc, char* argv[])
{
    using namespace std;
    string source;
    ifstream afile (argv[1] ,ios::in);
    if(afile.is_open()) {
        string buffer;
        while( getline(afile, buffer) ) {
            source.append(buffer);
        }
            afile.close();
        }
    else {
        cout << "Unable to open file" << endl;
        return -1;
    }
    auto tokenizer = make_shared<Tokenizer>(source);
    Parser parser(tokenizer);
    shared_ptr<ModuleRootNode> moduleNode;
    try {
        moduleNode = parser.Parse();
    } catch (char const* e) {
        cout << e;
        return 1;
    }
    if (moduleNode == nullptr) {
        cout << "Parsing error" << endl;
        return 1;
    }
    cout << endl;
    cout << endl;
    cout << "Compiling...";
    cout << endl;
	Compiler compiler;
	try {
		compiler.Visit(moduleNode.get());
    } catch (char const* e) {
        cout << e;
        return 1;
    }
	int i = 0;
	for (auto instruction : compiler.module().instructions) {
		cout << i << ": " << instruction.ToString() << endl;
		i++;
	}
	ModuleSerializerImpl serializer;
	serializer.Serialize("a.out", make_shared<Module>(compiler.module()));
	serializer.Deserialize("a.out");
    cout << endl;
	cout << "Executing..." << endl;
    cout << endl;
	VM vm;
	vm.Process(compiler.module());
    return 0;
}
