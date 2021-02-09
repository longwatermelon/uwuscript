#include "..\include\parseruwu.h"
#include <map>
#include <sstream>


Parser::Parser(const std::string& contents)
{
	lexer = Lexer(contents);
	current_token = lexer.get_next_token();
	prev_token = current_token;
}


void Parser::eat(TokenType token, const std::string& str)
{
	if (current_token.type_ == token)
	{
		if (current_token.value != str && str != "")
		{
			std::stringstream ss;
			ss << "lel breh stupid idoit cant even use proper grammar UwU\nexpected: " << str;
			throw std::runtime_error(ss.str());
		}

		prev_token = current_token;
		current_token = lexer.get_next_token();
	}
	else
	{
		std::string expected;

		std::map<TokenType, std::string> token_repr{
			{TokenType::TOKEN_ID, "identifier"},
			{TokenType::TOKEN_INT, "integer"},
			{TokenType::TOKEN_STRING, "string"},
			{TokenType::TOKEN_EOF, "end of file"}
		};

		std::stringstream ss;
		ss << "lmfapoooooooooo get a load of this guy got an error on line " << lexer.line_num << " what a stupid idot XD\n";
		throw std::runtime_error(ss.str());
	}
}


std::shared_ptr<AST> Parser::parse()
{
	return parse_statements();
}


std::shared_ptr<AST> Parser::parse_int()
{
	const std::shared_ptr<AST> ast_int = std::make_shared<AST>(AstType::AST_INT);
	std::stringstream(current_token.value) >> ast_int->int_value;
	eat(TokenType::TOKEN_INT);

	return ast_int;
}


std::shared_ptr<AST> Parser::parse_string()
{
	const std::shared_ptr<AST> ast_str = std::make_shared<AST>(AstType::AST_STRING);
	ast_str->string_value = current_token.value;
	eat(TokenType::TOKEN_STRING);
	
	return ast_str;
}


std::shared_ptr<AST> Parser::parse_id()
{
	if (current_token.value == "PLS")
		return parse_pls_request();

	return nullptr;
}

std::shared_ptr<AST> Parser::parse_variable_definition()
{
	const auto ret = std::make_shared<AST>(AstType::AST_VARIABLE_DEFINITION);

	eat(TokenType::TOKEN_ID, "DEFINE");

	ret->variable_definition_name = current_token.value;

	eat(TokenType::TOKEN_ID); // variable
	eat(TokenType::TOKEN_ID, "AS");

	ret->variable_definition_value = parse_expr();

	eat(TokenType::TOKEN_ID, "OWO");
	eat(TokenType::TOKEN_ID, "THANKS");

	return ret;
}


std::shared_ptr<AST> Parser::parse_function_call()
{
	eat(TokenType::TOKEN_ID, "CALL");
	const std::shared_ptr<AST> function_call = std::make_shared<AST>(AstType::AST_FUNCTION_CALL);

	function_call->function_call_name = current_token.value;

	eat(TokenType::TOKEN_ID);
	eat(TokenType::TOKEN_ID, "WITH");
	eat(TokenType::TOKEN_ID, "ARGUMENTS");
	
	std::shared_ptr<AST> expr = parse_expr();
	function_call->function_call_args.push_back(expr);

	while (current_token.value == "AND")
	{
		eat(TokenType::TOKEN_ID, "AND");

		expr = parse_expr();
		function_call->function_call_args.push_back(expr);
	}

	eat(TokenType::TOKEN_ID, "OWO");
	eat(TokenType::TOKEN_ID, "LEL");

	return function_call;
}


std::shared_ptr<AST> Parser::parse_pls_request()
{
	eat(TokenType::TOKEN_ID, "PLS");

	if (current_token.value == "DEFINE")
		return parse_variable_definition();
	if (current_token.value == "CALL")
		return parse_function_call();


	return nullptr;
}


std::shared_ptr<AST> Parser::parse_expr()
{
	switch (current_token.type_)
	{
	case TokenType::TOKEN_STRING: return parse_string();
	case TokenType::TOKEN_ID: return parse_id();
	case TokenType::TOKEN_INT: return parse_int();
	}

	return nullptr;
}


std::shared_ptr<AST> Parser::parse_statements()
{
	const auto ast = std::make_shared<AST>(AstType::AST_COMPOUND);

	auto expr = parse_expr();
	ast->compound_value.push_back(expr);

	while (lexer.idx < lexer.contents.size())
	{
		expr = parse_expr();

		if (expr == nullptr) break;

		ast->compound_value.push_back(expr);
	}

	return ast;
}