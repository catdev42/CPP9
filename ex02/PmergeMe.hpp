#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

#ifndef COLOR
#define COLOR
#define GREY "\033[0;30m"
#define RESET "\033[0m"
#endif

typedef struct intInfo
{
    int n;
    int pos;
    bool operator<(struct intInfo a) { return (this->n < a.n); }
} intM;

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(char **argv);
    ~PmergeMe();
    template <typename Cont>
    Cont sort(Cont main);

private:
    std::vector<int> sortedVec;
    std::deque<int> sortedDeq;
    
    time_t startTime;
    time_t endTime;

    float time();
    std::string containerType();



    PmergeMe(PmergeMe const &other) { (void)other; }
    PmergeMe &operator=(PmergeMe const &other) { (void)other; }
};

std::ostream &operator<<(std::ostream &o, PmergeMe const &infile);

#endif
