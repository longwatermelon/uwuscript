#pragma once
#include <string>
#include <memory>
#include <vector>


enum class AstType
{
	AST_VARIABLE_DEFINITION,
	AST_INT,
	AST_STRING,
	AST_FUNCTION_CALL,
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


	AST(AstType type)
		: type(type) {}
};