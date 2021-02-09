#include "../include/visitoruwu.h"
#include <sstream>
#include <iostream>


std::shared_ptr<AST> Visitor::builtin_print(std::vector<std::shared_ptr<AST>> args)
{
	for (auto& arg : args)
	{
		std::shared_ptr<AST> ast = visit(arg);
		
		switch (ast->type)
		{
		case AstType::AST_STRING: std::cout << ast->string_value << " "; break;
		case AstType::AST_INT: std::cout << ast->int_value << " "; break;
		case AstType::AST_VARIABLE: {
			std::shared_ptr<AST> temp = goto_root_of_variable(ast);
			switch (temp->type)
			{
			case AstType::AST_STRING: std::cout << temp->string_value << " "; break;
			case AstType::AST_INT: std::cout << temp->int_value << " "; break;
			}
		}
		default: std::cout << "breh OwO gonna haf to reject this variable i cant print it :pleading_face:\n"; break;
		}
	}

	std::cout << "\n";

	return std::make_shared<AST>(AstType::AST_NOOP);
}


std::shared_ptr<AST> Visitor::visit(std::shared_ptr<AST> node)
{
	switch (node->type)
	{
	case AstType::AST_VARIABLE_DEFINITION: return visit_variable_definition(node);
	case AstType::AST_STRING: return node;
	case AstType::AST_INT: return node;
	case AstType::AST_FUNCTION_CALL: return visit_function_call(node);
	case AstType::AST_VARIABLE: return visit_var(node);
	case AstType::AST_COMPOUND: return visit_compound(node);
	case AstType::AST_NOOP: return node;
	}

	std::stringstream ss;
	ss << "lel BREH i dont recognize wtf is hits UwU\n";
	throw std::runtime_error(ss.str());

	return nullptr;
}


std::shared_ptr<AST> Visitor::visit_variable_definition(std::shared_ptr<AST> node)
{
	for (auto& def : variable_defs)
	{
		if (node->variable_definition_name == def->variable_definition_name)
		{
			modify_variable(def, node);
			return node;
		}
	}

	variable_defs.push_back(node);
	return node;
}


void Visitor::modify_variable(std::shared_ptr<AST> variable, std::shared_ptr<AST> node)
{
	variable->variable_definition_value = node->variable_definition_value;
}


std::shared_ptr<AST> Visitor::goto_root_of_variable(std::shared_ptr<AST> variable)
{
	std::shared_ptr<AST> temp = visit(variable->variable_definition_value);

	while (true)
	{
		if (temp->variable_definition_value == nullptr)
			break;

		temp = visit(temp->variable_definition_value);
	}

	return temp;
}


std::shared_ptr<AST> Visitor::visit_var(std::shared_ptr<AST> node)
{
	for (auto& def : variable_defs)
	{
		if (def->variable_definition_name == node->variable_name || def->variable_definition_name == node->variable_name)
		{
			return visit(def->variable_definition_value);
		}
	}

	std::stringstream ss;
	ss << "lmfpao what stpid idiot dint even define variable lel xddddddddddddddd\n";
	throw std::runtime_error(ss.str());
}


std::shared_ptr<AST> Visitor::visit_compound(std::shared_ptr<AST> node)
{
	for (auto& item : node->compound_value)
		visit(item);

	return std::make_shared<AST>(AstType::AST_NOOP);
}


std::shared_ptr<AST> Visitor::visit_function_call(std::shared_ptr<AST> node)
{
	if (node->function_call_name == "UWUPRINT")
		return builtin_print(node->function_call_args);

	throw std::runtime_error("u trying to brak me or sumtg? :angry: thats not a vaild function");
}