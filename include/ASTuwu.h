#pragma once
#include <string>
#include <memory>
#include <vector>


enum class AstType
{
	AST_VARIABLE_DEFINITION,
	AST_VARIABLE,
	AST_INT,
	AST_STRING,
	AST_FUNCTION_CALL,
	AST_FUNCTION_DEFINITION,
	AST_COMPOUND,
	AST_NOOP
};


class AST
{
public:
	AstType type{ AstType::AST_NOOP };

	// variable def
	std::string variable_definition_name;
	std::shared_ptr<AST> variable_definition_value;

	// var
	std::string variable_name;

	// string
	std::string string_value;

	// int
	int int_value{ 0 };

	// compound
	std::vector<std::shared_ptr<AST>> compound_value;

	// function call
	std::string function_call_name;
	std::vector<std::shared_ptr<AST>> function_call_args;

	// function definition
	std::string function_definition_name;
	std::vector<std::shared_ptr<AST>> function_definition_body;
	std::vector<std::shared_ptr<AST>> function_definition_params;

	// error fields
	size_t error_index{ 0 };
	size_t error_line_num{ 0 };


	AST(AstType type)
		: type(type) {}
};