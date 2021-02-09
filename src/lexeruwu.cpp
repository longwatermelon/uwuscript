#include "../include/lexeruwu.h"
#include <iostream>


Lexer::Lexer(const std::string& contents)
	: contents(contents)
{
	if (contents.empty()) throw std::runtime_error("File is either empty or does not exist.");

	current_character = contents.at(idx);
}


void Lexer::advance()
{
	if (idx < contents.size() - 1)
	{
		++idx;
		current_character = contents.at(idx);
	}
}


void Lexer::skip_ws()
{
	while (isspace(current_character)) advance();
}


std::string Lexer::collect_string()
{
	const auto start_idx = idx + 1;
	advance(); // "

	while (current_character != '"' && idx < contents.size() && current_character != 10) // 10 for nl character
		advance();

	const auto str = contents.substr(start_idx, idx - start_idx);
	advance(); // "
	return str;
}


std::string Lexer::collect_int()
{
	std::string integer;

	while (isdigit(current_character))
	{
		integer += current_character;
		advance();
	}

	return integer;
}



std::string Lexer::collect_id()
{
	const auto start_idx = idx;

	while ((isalnum(current_character) || current_character == '_') && idx < contents.size())
		advance();

	const auto ret = contents.substr(start_idx, idx - start_idx);
	return ret;
}


Token Lexer::get_next_token()
{
	while (idx < contents.size() - 1)
	{
		prev_idx = idx;

		if (isspace(current_character) && current_character != 10)
			skip_ws();

		if (isdigit(current_character))
			return Token(TokenType::TOKEN_INT, collect_int());

		if (isalnum(current_character))
			return Token(TokenType::TOKEN_ID, collect_id());

		if (current_character == '"')
			return Token(TokenType::TOKEN_STRING, collect_string());


		advance();
		++line_num;
	}

	return Token(TokenType::TOKEN_EOF, "");
}