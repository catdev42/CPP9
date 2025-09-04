#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <ctime>
#include <sstream>
#include <exception>
#include <climits>
#include <fstream>

#ifndef COLOR
#define COLOR
#define GREY "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#endif

/*
std::ofstream debug_log("debug_log.txt");
*/

typedef struct intInfo
{
    int n;
    int pos;
    bool operator<(const struct intInfo &a) const { return this->n < a.n; }
    bool operator>(const struct intInfo &a) const { return this->n > a.n; }

} intM;

template <typename Cont>
class PmergeMe
{
protected:
    typedef typename Cont::value_type value_type;

public:
    PmergeMe() {}
    PmergeMe(int argc, char **argv) { sort(argc, argv); }
    ~PmergeMe() {}

    const Cont getSortedContainer() const { return sorted; }
    const Cont getUnsortedContainer() const { return unsorted; }
    double getElapsed() const { return elapsed; }
    bool is_sorted() const { return is_sorted_by_n(sorted); }

    Cont sort(int argc, char **argv);

private:
    PmergeMe(PmergeMe const &other) { (void)other; }
    PmergeMe &operator=(PmergeMe const &other) { (void)other; }

    Cont sorted;
    Cont unsorted;
    double elapsed;

    Cont sort(Cont &numbers, size_t &inserted);
    Cont fillMain(Cont &numbers, Cont &main, bool &straggler);
    void orderPend(const Cont &numbers, Cont &main, Cont &pend);
    void insert(Cont &main, const Cont &pend, size_t &inserted);

    /* helpers*/
    size_t numAmount;
    static size_t jacobs[];
    time_t startTime;
    time_t endTime;
    Cont small_sort(Cont &numbers);
    void check_validity();
    Cont initNumbers(int argc, char **argv);
    bool is_sorted_by_n(const Cont &c) const;

    template <typename T, typename U>
    struct is_same
    {
        enum
        {
            value = 0
        };
    };
    template <typename T>
    struct is_same<T, T>
    {
        enum
        {
            value = 1
        };
    };

    /*
    void log_container(const Cont &c, const std::string &label, bool pos = 0);
    std::ostream &log_container(std::ostream &o, const Cont &c, const std::string &label, bool pos = 0);
    */
};

template <typename Cont>
size_t PmergeMe<Cont>::jacobs[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};

#include "PmergeMe.tpp"

template <typename Cont>
std::ostream &operator<<(std::ostream &o, PmergeMe<Cont> const &infile)
{
    const Cont sorted = infile.getSortedContainer();
    const Cont unsorted = infile.getUnsortedContainer();

    if (!infile.is_sorted())
        throw std::runtime_error("Its not sorted! ERROR BAD PROGRAM");
    o << "Before: ";
    for (typename Cont::const_iterator it = unsorted.begin(); it != unsorted.end(); ++it)
    {
        if (it != unsorted.begin())
            o << ", ";
        o << it->n;
    }
    o << std::endl;
    o << "After: ";
    for (typename Cont::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
    {
        if (it != sorted.begin())
            o << ", ";
        o << it->n;
    }
    return o;
}

#endif
