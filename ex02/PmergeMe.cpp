#include "PmergeMe.hpp"
#include <iostream>

/********************************************/
/********************************************/
/******          CONSTRUCTORS          ******/

PmergeMe::PmergeMe()
{
    std::cout << GREY << "PmergeMe default constructor" << RESET << std::endl;
    return;
}

PmergeMe::PmergeMe(PmergeMe const &other)
{
    std::cout << GREY << "PmergeMe copy constructor" << RESET << std::endl;
    /*TODO*/;
    return;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
    std::cout << GREY << "PmergeMe copy assignment operator" << RESET << std::endl;
    if (this != &other)
    {
      /*TODO*/;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
    std::cout << GREY << "PmergeMe destructor" << RESET << std::endl;
    return;
}

/********************************************/
/********************************************/
/******        MEMBER FUNCTIONS        ******/

/********************************************/
/********************************************/
/******            STREAM              ******/

std::ostream &operator<<(std::ostream &o, const PmergeMe &infile)
{
    o << "";
    return o;
}

/********************************************/
/********************************************/
/****** PRIVATE ******/
