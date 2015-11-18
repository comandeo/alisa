#ifndef __TOKEN_H
#define __TOKEN_H 1

#include <iostream>
#include <string>

enum TokenType {
	UNKNOWN,
	EPSILON,
	IDENTIFIER,
	L_BRACE,
	R_BRACE,
	L_CURLY_BRACE,
	R_CURLY_BRACE,
	COLON,
	SEMICOLON,
	COMMA,
	STRING_LITERAL,
	INTEGER,
	EQ,
	// KEYWORDS
	LET,
	FN
};

struct Token {
	Token(TokenType typeP = UNKNOWN, std::string valueP = "")
		: type(typeP), value(valueP) {}
	TokenType type;
	std::string value;

	void Trace()
	{
		if (type == IDENTIFIER) {
			std::cout << "Token: IDENTIFIER (" << value << ")" << std::endl;
		} else if (type == INTEGER) {
			std::cout << "Token: INTEGER (" << value << ")" << std::endl;
		} else {
			std::cout << "Token: " << value << std::endl;
		}
	}
};

#endif
