#include <cctype>
#include "tokenizer.hpp"

Tokenizer::Tokenizer(std::string& source)
	: source_(source)
{
}

Token Tokenizer::GetNextToken()
{
	using namespace std;
	if (source_.length() == 0) {
		return Token(EPSILON);
	}
	int i = 0;
	while(isspace(source_[i])) {
		i++;
	}
	if (i > 0) {
		source_.erase(0, i);
	}
	string tokenValue;
	switch (source_[0]) {
		case '(':
		source_.erase(0, 1);
		return Token(L_BRACE, "(");

		case ')':
		source_.erase(0, 1);
		return Token(R_BRACE, ")");

		case '{':
		source_.erase(0, 1);
		return Token(L_CURLY_BRACE, "{");

		case '}':
		source_.erase(0, 1);
		return Token(R_CURLY_BRACE, "}");

		case ':':
		source_.erase(0, 1);
		return Token(COLON, ":");

		case ';':
		source_.erase(0, 1);
		return Token(SEMICOLON, ";");

		case ',':
		source_.erase(0, 1);
		return Token(COMMA, ";");

		case '=':
		source_.erase(0, 1);
		return Token(EQ, "=");

		case '"':
		i = 1;
		while (source_[i] != '"') {
			i++;
		}
		if (i > 1) {
			tokenValue = source_.substr(1, i-1);
		} else {
			tokenValue = "";
		}
		source_.erase(0, i + 1);
		return Token(STRING_LITERAL, tokenValue);

		default:
		i = 1;
		while (
			isdigit(source_[i]) ||
			isalnum(source_[i]) ||
			source_[i] == '_'
		) {
			i++;
		}
		tokenValue = source_.substr(0, i);
		source_.erase(0, i);
		return DetectLongToken(tokenValue);
	}
}

Token Tokenizer::DetectLongToken(std::string tokenValue)
{
	Token token;
	token.value = tokenValue;
	if (tokenValue == "let") {
		token.type = LET;
	} else if (tokenValue == "fn") {
		token.type = FN;
	} else if (isdigit(tokenValue[0])) {
		token.type = INTEGER;
	} else {
		token.type = IDENTIFIER;
	}
	return token;
}
