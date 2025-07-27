#include "RPN.hpp"
#include <iostream>
#include <string>

/********************************************/
/********************************************/
/****** MEMBER FUNCTIONS ******/

int RPN::processRPN(std::string str)
{

    std::stack<int> stacky;
    std::stringstream ss(str);
    std::string token;
    bool addnumber = false;
    int number;

    while (ss >> token)
    {
        int a = 0;
        int b = 0;
        switch (token[0])
        {
        case '+':
        case '-':
        case '*':
        case '/':
            b = stacky.top();
            stacky.pop();
            a = stacky.top();
            stacky.pop();
            if (token[0] == '/' && b == 0)
                throw std::runtime_error("Division by 0");
            stacky.push(calculate(a, b, token[0]));
            break;
        default:
            addnumber = true;
        }
        if (addnumber)
        {
            std::stringstream tokenss(token);
            if (!(tokenss >> number))
            {
                throw std::runtime_error("Error");
                return 1;
            }
            stacky.push(number);
        }
        addnumber = false;
    }
    if (stacky.size() != 1)
        throw std::runtime_error("Error: empty stack");
    return stacky.top();
}

/********************************************/
/********************************************/
/****** PRIVATE MEMBER FUNCTIONS ******/
int RPN::calculate(int a, int b, char oper)
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

/********************************************/
/********************************************/
/****** STREAM ******/

/********************************************/
/********************************************/
/****** PRIVATE CONSTRUCTORS******/

RPN::RPN()
{
    std::cout << GREY << "RPN default constructor" << RESET << std::endl;
    return;
}

RPN::RPN(RPN const &other)
{
    std::cout << GREY << "RPN copy constructor" << RESET << std::endl;
    *this = other;
    return;
}

RPN &RPN::operator=(RPN const &other)
{
    std::cout << GREY << "RPN copy assignment operator" << RESET << std::endl;
    if (this != &other)
    {
        (void)other;
    }
    return *this;
}

RPN::~RPN()
{
    std::cout << GREY << "RPN destructor" << RESET << std::endl;
    return;
}
