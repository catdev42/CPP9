#include <iostream>
#include <stack>
#include <sstream>
#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: must be 2 arguments" << std::endl;
		return (0);
	}

	std::string str = argv[1];
	int result;
	try
	{
		result = RPN::processRPN(str);
		std::cout << result << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
