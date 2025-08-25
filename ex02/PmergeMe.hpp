#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

#ifndef COLOR
#define COLOR
#define GREY "\033[0;30m"
#define RESET "\033[0m"
#endif

class PmergeMe {  
public:
    PmergeMe();
    PmergeMe(PmergeMe const &other);
    PmergeMe &operator=(PmergeMe const &other);
    ~PmergeMe();
private:
};

std::ostream &operator<<(std::ostream &o, PmergeMe const &infile);

#endif
