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

std::ofstream debug_log("debug_log.txt");

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

    Cont sort(int argc, char **argv)
    {
        Cont numbers;
        size_t inserted;
        startTime = std::clock();
        check_validity();
        numbers = initNumbers(argc, argv);
        unsorted = numbers;
        sort(numbers, inserted);
        endTime = std::clock();
        elapsed = double(endTime - startTime) / CLOCKS_PER_SEC;

        return this->sorted;
    }

    Cont sort(Cont &numbers, size_t &inserted)
    {
        Cont main;
        Cont pend;
        intM straggler;
        bool strag = false;

        if (numbers.size() == 1)
            return numbers;
        if (numbers.size() == 2)
        {
            typename Cont::iterator it = numbers.begin();
            typename Cont::iterator itOdd = it;
            itOdd++;
            if (itOdd->n < it->n)
                std::iter_swap(itOdd, it);
            return numbers;
        }
        if (numbers.size() == 3)
        {
            typename Cont::iterator zero = numbers.begin();
            typename Cont::iterator one = zero;
            one++;
            typename Cont::iterator two = one;
            two++;
            if (*zero > *one && *zero > *two)
                std::iter_swap(zero, two);
            else if (*one > *zero && *one > *two)
                std::iter_swap(one, two);
            if (*zero > *one)
                std::iter_swap(zero, one);
            sorted = numbers;
            return numbers;
        }
        fillMain(numbers, main, strag);
        if (strag)
            straggler = numbers.back();
        main = sort(main, inserted);
        orderPend(numbers, main, pend);
        insert(main, pend, inserted);
        if (strag)
        {
            typename Cont::iterator pos = std::lower_bound(main.begin(), main.end(), straggler);
            main.insert(pos, straggler);
            ++inserted;
        }
        if (main.size() == numAmount)
            sorted = main;
        return main;
    }

    /*gives new indexes to main*/
    void fillMain(Cont &numbers, Cont &main, bool &straggler)
    {
        int i;

        typename Cont::iterator it = numbers.begin();
        typename Cont::iterator itOdd = numbers.begin();
        typename Cont::iterator end = numbers.end();
        itOdd++;
        i = 0;
        while (it != end && itOdd != end)
        {
            if (it->n > itOdd->n)
            {
                std::swap(*it, *itOdd);
                int temp = it->pos;
                it->pos = itOdd->pos;
                itOdd->pos = temp;
            }
            main.push_back(*itOdd);
            main.back().pos = i;
            i++;
            std::advance(it, 2);
            std::advance(itOdd, 2);
        }
        if (it != end)
        {
            straggler = true;
        }
    }

    void orderPend(const Cont &numbers, Cont &main, Cont &pend);
    void insert(Cont &main, const Cont &pend, size_t &inserted)
    {
        size_t j;
        size_t index;
        size_t jsize;
        bool finish = 0;

        j = 0;
        // log_container(main, "\nmain before insert");
        // log_container(pend, "pend before insert");

        if (*pend.begin() < *main.begin() && ++inserted)
            main.insert(main.begin(), *pend.begin()); // check
        else
            main.insert(++main.begin(), *pend.begin()); // check

        j += 2;
        jsize = sizeof(jacobs) / sizeof(jacobs[0]);
        size_t maxIndexToSearch;
        while (!finish)
        {
            index = jacobs[j] - 1;
            if (index >= pend.size() - 1 || j >= jsize)
            {
                index = pend.size() - 1;
                finish = 1;
            }
            maxIndexToSearch = jacobs[j] + inserted;
            if (maxIndexToSearch >= main.size() - 1 || j > jsize)
                maxIndexToSearch = main.size() - 1;

            while (index >= jacobs[j - 1])
            {
                log_container(main, "\nmain before lower_bound");
                log_container(pend, "pend before lower_bound");

                typename Cont::iterator itMaxSearch;
                itMaxSearch = main.begin();
                std::advance(itMaxSearch, maxIndexToSearch + 2);
                typename Cont::const_iterator itItem = pend.begin();
                std::advance(itItem, index);
                typename Cont::iterator itInsert = main.begin();
                itInsert = std::lower_bound(main.begin(), itMaxSearch, *itItem);
                if (itItem->n > itInsert->n)
                {
                    debug_log << "LOG: \n"
                              << "index:[" << index << "]; \n"
                              << "inserted:[" << inserted << "]; \n"
                              << "itItem->n:[" << itItem->n << "]; \n"
                              << "itInsert->n:[" << itInsert->n << "]; \n"
                              << "maxIndexToSearch[" << maxIndexToSearch << "]; \n"
                              << "main[maxIndexToSearch]:[" << main[maxIndexToSearch].n << "]; \n"
                              << "last 2 lines should have the same num maybe"
                              << std::endl;
                    throw std::runtime_error("INSERT ERROR");
                }
                main.insert(itInsert, *itItem);
                ++inserted;
                // if (!is_sorted_by_n(main))

                log_container(main, "main after  lower_bound");
                index--;
            }
            j++;
            if (finish)
                break;
        }
        // log_container(main, "main after  insert");
    }

private:
    PmergeMe(PmergeMe const &other) { (void)other; }
    PmergeMe &operator=(PmergeMe const &other) { (void)other; }

    Cont sorted;
    Cont unsorted;
    double elapsed;

    size_t numAmount;
    static size_t jacobs[];
    time_t startTime;
    time_t endTime;

    Cont initNumbers(int argc, char **argv);

    void log_container(const Cont &c, const std::string &label);
    bool is_sorted_by_n(const Cont &c);

    void check_validity();
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
};

template <typename Cont>
size_t PmergeMe<Cont>::jacobs[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};

#include "PmergeMe.tpp"

template <typename Cont>
std::ostream &operator<<(std::ostream &o, PmergeMe<Cont> const &infile)
{
    const Cont sorted = infile.getSortedContainer();
    const Cont unsorted = infile.getUnsortedContainer();

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
