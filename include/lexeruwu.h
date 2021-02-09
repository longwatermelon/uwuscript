#pragma once
#include "tokenuwu.h"
#include <string>


class Lexer
{
public:
	std::string contents;
	size_t idx{ 0 };
	size_t prev_idx{ 0 };
	size_t line_num{ 0 };
	char current_character{ ' ' };


	Lexer() = default;
	
	Lexer(const std::string& contents);

	void advance();

	void skip_ws();

	std::string collect_string();

	std::string collect_int();

	std::string collect_id();

	Token get_next_token();
};