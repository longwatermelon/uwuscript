#include <iostream>
#include "../include/parseruwu.h"
#include "../include/visitoruwu.h"
#include <fstream>
#include <sstream>
#include <iostream>


std::string read_file(const std::string& fp)
{
	std::ifstream infile;
	infile.open(fp);

	std::stringstream ss;
	std::string line;

	while (std::getline(infile, line)) ss << line << "\n";

	infile.close();
	return ss.str();
}


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "No file specified\n";
		return 1;
	}

	std::string contents = read_file(argv[1]);
	Parser parser(contents);
	Visitor visitor;

	try
	{
		std::shared_ptr<AST> root = parser.parse();
		visitor.visit(root);
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << "\n";
	}

	return 0;
}