#include <fstream>
#include <iostream>
#include <memory>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "ast_printer.hpp"
#include "compiler.hpp"

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
    std::shared_ptr<ModuleRootNode> moduleNode;
    try {
        moduleNode = parser.Parse();
    } catch (char const* e) {
        std::cout << e;
        return 1;
    }
    if (moduleNode == nullptr) {
        std::cout << "Parsing error" << std::endl;
        return 1;
    }
    std::cout << std::endl;
    AstPrinter astPrinter;
    astPrinter.Visit(moduleNode.get());

    std::cout << std::endl;
    std::cout << "Compiling...";
    std::cout << std::endl;
	Compiler compiler;
	try {
		compiler.Visit(moduleNode.get());
    } catch (char const* e) {
        std::cout << e;
        return 1;
    }
    return 0;
}
