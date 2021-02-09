#pragma once
#include <string>


enum class TokenType
{
	TOKEN_ID,
	TOKEN_STRING,
	TOKEN_INT,
	TOKEN_EOF
};


class Token
{
public:
	std::string value;
	TokenType type_{ TokenType::TOKEN_EOF };

	Token() = default;

	Token(TokenType type, const std::string& value)
		: type_(type), value(value) {}
};