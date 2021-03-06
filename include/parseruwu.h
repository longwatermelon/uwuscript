#pragma once
#include "tokenuwu.h"
#include "lexeruwu.h"
#include "ASTuwu.h"
#include <memory>


class Parser
{
public:
	Token current_token;
	Token prev_token;
	Lexer lexer;

	Parser(const std::string& contents);

	void eat(TokenType token, const std::string& str = "");
	void eat_multiple(const std::vector<std::string>& strings);

	std::shared_ptr<AST> parse();

	std::shared_ptr<AST> parse_int();
	std::shared_ptr<AST> parse_string();
	std::shared_ptr<AST> parse_id();

	std::shared_ptr<AST> parse_variable_definition();
	std::shared_ptr<AST> parse_variable();

	std::shared_ptr<AST> parse_function_call();
	std::shared_ptr<AST> parse_function_definition();

	std::shared_ptr<AST> parse_pls_request();

	std::shared_ptr<AST> parse_expr();

	std::shared_ptr<AST> parse_statements();

	void init_error_values(std::shared_ptr<AST> node);
};