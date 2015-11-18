#ifndef __TOKENIZER_H
#define __TOKENIZER_H 1

#include <string>
#include "token.hpp"

class Tokenizer {
public:
	Tokenizer(std::string& source);
	Token GetNextToken();
private:
	Token DetectLongToken(std::string tokenValue);
	std::string source_;
};
#endif
