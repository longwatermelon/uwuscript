#pragma once
#include "ASTuwu.h"
#include <memory>
#include <vector>
#include <string>


class Visitor
{
public:
	std::vector<std::shared_ptr<AST>> variable_defs;
	std::vector<std::shared_ptr<AST>> function_defs;


	std::shared_ptr<AST> builtin_print(std::vector<std::shared_ptr<AST>> args);

	std::shared_ptr<AST> visit(std::shared_ptr<AST> node);

	std::shared_ptr<AST> visit_variable_definition(std::shared_ptr<AST> node);
	void modify_variable(std::shared_ptr<AST> variable, std::shared_ptr<AST> node);
	std::shared_ptr<AST> goto_root_of_variable(std::shared_ptr<AST> variable);
	std::shared_ptr<AST> visit_var(std::shared_ptr<AST> node);

	std::shared_ptr<AST> visit_compound(std::shared_ptr<AST> node);

	std::shared_ptr<AST> visit_function_call(std::shared_ptr<AST> node);
	std::shared_ptr<AST> visit_function_definition(std::shared_ptr<AST> node);
	std::shared_ptr<AST> get_function(const std::string& name);
};