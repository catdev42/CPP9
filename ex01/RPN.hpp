#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

#ifndef COLOR
#define COLOR
#define GREY "\033[0;30m"
#define RESET "\033[0m"
#endif

class RPN
{
public:
    static int processRPN(std::string str);

private:
    static int calculate(int a, int b, char oper);

    RPN();
    RPN(RPN const &other);
    RPN &operator=(RPN const &other);
    ~RPN();
};

#endif
