#ifndef __TOKEN_H
#define __TOKEN_H 1

#include <iostream>
#include <string>

enum class TokenType {
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
	FN,
    RETURN
};

struct Token {
	Token(TokenType typeP = TokenType::UNKNOWN, std::string valueP = "")
		: type(typeP), value(valueP) {}
	TokenType type;
	std::string value;

	std::string ToString()
	{
		std::string result = "";
		if (type == TokenType::IDENTIFIER) {
			result.append("Token: IDENTIFIER (").append(value).append(")");
		} else if (type == TokenType::INTEGER) {
			result.append("Token: INTEGER (").append(value).append(")");
		} else {
			result.append("Token: ").append(value);
		}
		return result;
	}
};

#endif
