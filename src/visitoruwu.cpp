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
		default: std::cout << "breh OwO noni wtf is this XD line " << ast->error_line_num; break;
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
	case AstType::AST_FUNCTION_DEFINITION: return visit_function_definition(node);
	case AstType::AST_NOOP: return node;
	}

	std::stringstream ss;
	ss << "lel BREH i dont recognize wtf is hits UwU\nline " << node->error_line_num << " wtf?\n";
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
		if (def->variable_definition_name == node->variable_name)
		{
			return visit(def->variable_definition_value);
		}
	}

	std::stringstream ss;
	ss << "lmfpao what stpid idiot dint even define variable lel xddddddddddddddd line " << node->error_line_num << " what tje frick is " << node->variable_name << "\n";
	throw std::runtime_error(ss.str());

	return nullptr;
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

	std::shared_ptr<AST> func_def = get_function(node->function_call_name);

	if (func_def->function_definition_params.size() != node->function_call_args.size())
	{
		std::stringstream ss;
		ss << "breh your such a coding novice lel XD didnt even supply the right amount of aergewments lel idk how to spell it XD on line "
			<< node->error_line_num << "\n";
		throw std::runtime_error(ss.str());
	}


	std::shared_ptr<AST> ast;

	if (node->function_call_args.size() > 0 && node->function_call_args[0]->type != AstType::AST_NOOP)
	{
		for (int i = 0; i < node->function_call_args.size(); ++i)
		{
			const auto vardef = std::make_shared<AST>(AstType::AST_VARIABLE_DEFINITION);

			vardef->variable_definition_value = node->function_call_args[i];
			vardef->variable_definition_name = func_def->function_definition_params[i]->variable_name;

			visit_variable_definition(vardef);
		}

		for (auto& item : func_def->function_definition_body)
			const auto ast = visit(item);
	}
	else
	{
		for (auto& item : func_def->function_definition_body)
			ast = visit(item);
	}

	return ast;
}


std::shared_ptr<AST> Visitor::visit_function_definition(std::shared_ptr<AST> node)
{
	function_defs.push_back(node);

	return node;
}


std::shared_ptr<AST> Visitor::get_function(const std::string& name)
{
	for (auto& item : function_defs)
	{
		if (item->function_definition_name == name)
			return item;
	}

	std::stringstream ss;
	ss << "LEL stupid idoti dont invalid function LMFAPOOOOOOOOOO XDDDDDDDD\n";
	throw std::runtime_error(ss.str());

	return nullptr;
}
