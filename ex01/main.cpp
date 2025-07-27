#include <iostream>
// #include "MutantStack.hpp"
#include <stack>

int calculate(int a, int b, char oper)
{
	switch (oper)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: must be 2 arguments" << std::endl;
		return (0);
	}

	std::stack<int> stacky;
	std::string str = argv[1];
	int i = 0;
	while (str[i] != 0)
	{
		int a = 0;
		int b = 0;
		switch (str[i])
		{
		case ' ':
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			a = stacky.top();
			stacky.pop();
			b = stacky.top();
			stacky.pop();
			stacky.push(calculate(a, b, str[i]));
			i++;
			break;
		default:
			stacky.push(std::atoi(&str[i]));
		}
		std::cout << stacky.top() << std::endl;

		i++;
	}
	std::cout << stacky.top() << std::endl;
}
