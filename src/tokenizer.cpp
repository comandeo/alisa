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
		return Token(TokenType::EPSILON);
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
		return Token(TokenType::L_BRACE, "(");

		case ')':
		source_.erase(0, 1);
		return Token(TokenType::R_BRACE, ")");

		case '{':
		source_.erase(0, 1);
		return Token(TokenType::L_CURLY_BRACE, "{");

		case '}':
		source_.erase(0, 1);
		return Token(TokenType::R_CURLY_BRACE, "}");

		case ':':
		source_.erase(0, 1);
		return Token(TokenType::COLON, ":");

		case ';':
		source_.erase(0, 1);
		return Token(TokenType::SEMICOLON, ";");

		case ',':
		source_.erase(0, 1);
		return Token(TokenType::COMMA, ";");

		case '=':
		source_.erase(0, 1);
		return Token(TokenType::EQ, "=");

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
		return Token(TokenType::STRING_LITERAL, tokenValue);

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
		token.type = TokenType::LET;
	} else if (tokenValue == "fn") {
		token.type = TokenType::FN;
    } else if (tokenValue == "return") {
        token.type = TokenType::RETURN;
	} else if (isdigit(tokenValue[0])) {
		token.type = TokenType::INTEGER;
	} else {
		token.type = TokenType::IDENTIFIER;
	}
	return token;
}
