#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <sstream>
#include <exception>

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

/*
Must be initialized ith the correct container holding structs intM
*/
template <typename Cont>
class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(int argc, char **argv);
    ~PmergeMe();
    Cont sort(int argc, char **argv)
    {
        Cont numbers;
        numbers = initNumbers(char **argv);
        sort(numbers);
    }

    Cont initNumbers(int argc, char **argv)
    {
        Cont main;

        for (int i = 1; i < argc; i++)
        {
            long num;
            int n;
            std::istringstream s = argv[i];
            if (!(s >> num) || num > INT_MAX || num < INT_MIN)
            {
                std::cerr << "Error: not an int: " << argv[i] << std::endl;
                throw std::runtime_error("Error: not an int");
            }
            n = static_cast<int> num;
            intM elem;
            elem.n = n;
            elem.pos = i;
            main.push_back(num);
        }
        return main;
    }

    void fillMain(const Cont &numbers, Cont &main, bool &straggler)
    {
        int i;

        Cont::iterator it = main.begin();
        Cont::iterator itOdd = main.begin();
        Cont::iterator end = main.end();
        itOdd++;
        i = 0;
        while (itOdd != end && it != end)
        {
            intM *left = &(*it);
            intM *right = &(*itOdd);
            if (left->n > right->n)
                std::swap(*it, *itOdd);
            main.push_back(*right);
            main.back().pos = i;
            i++;
            it++;
            itOdd++;
        }
        if (it != end)
            straggler = true;
    }



    Cont sort(Cont &numbers)
    {
        Cont main;
        Cont pend;
        intM straggler;
        bool strag = false;

        if (numbers.size() == 1)
            return numbers;
        if (numbers.size() == 2)
        {
            itOdd->n < it->n;
            std::iter_swap(itOdd, it);
            return numbers;
        }
        fillMain(numbers, main, straggler);
        // main pos indexes: 0 1 2 3 4 5
        if (strag)
            straggler = numbers.back();
        sort(main);

        orderPend(numbers, main, pend);
        insert(pend, main);
        Cont::it pos = main.lower_bound(main.begin(), main.end(), straggler);
        main.insert(inPos, straggler);
        if (main.size() == number.size())
            sorted = main;
        // main positions have to be restored before return
        return main;
    }
    /**
     * main pos indexes:  2 0 3 1 4 5
     * need to restore the pos indexes to match original array that included all nums
     * main pos indexes: 5 1 7 3 9 11
     * find pend elements: 4 0 6 2 8 10
     * */
    void orderPend(const Cont &numbers, Cont &main, Cont &pend)
    {
        Cont::iterator numIt;
        Cont::iterator it = main.begin();
        Cont::iterator end = main.end();

        while (it != end)
        {
            numIt = numbers.begin();
            std::advance(numIt, ( it->pos * 2));
            pend.push_back(*numIt); //add elements to pend
            //update pos member in struct so it matches the previous recursive call
            it->pos = pos * 2 + 1; 
            it++;
        }
    }

private:
    static size_t jacobs[];
    Cont sorted;

    time_t startTime;
    time_t endTime;

    float time();
    // std::string containerType();

    PmergeMe(PmergeMe const &other) { (void)other; }
    PmergeMe &operator=(PmergeMe const &other) { (void)other; }
};

template <typename Cont>
size_t PmergeMe<Cont>::jacobs[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};

template <typename Cont>
std::ostream &operator<<(std::ostream &o, PmergeMe<Cont> const &infile);

#endif
