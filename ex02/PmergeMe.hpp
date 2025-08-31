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
    /* getters */
    const Cont getSortedContainer() const { return sorted; }
    const Cont getUnsortedContainer() const { return unsorted; }
    double getElapsed() const { return elapsed; }

    bool is_sorted() const
    {
        return is_sorted_by_n(sorted);
    }

    Cont sort(int argc, char **argv)
    {
        Cont numbers;
        size_t inserted = 0;
        startTime = std::clock();
        check_validity();
        numbers = initNumbers(argc, argv);
        unsorted = numbers;
        sort(numbers, inserted);
        endTime = std::clock();
        elapsed = double(endTime - startTime) / CLOCKS_PER_SEC;
        return this->sorted;
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

    void check_validity();
    Cont initNumbers(int argc, char **argv);

    Cont small_sort(Cont &numbers)
    ;
    Cont sort(Cont &numbers, size_t &inserted)
    {

        Cont main;
        Cont pend;
        intM straggler;
        bool strag = false;

        if (numbers.size() <= 3)
            return small_sort(numbers);

        numbers = fillMain(numbers, main, strag);
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

    void insert(Cont &main, const Cont &pend, size_t &inserted)
    {
        size_t j;
        size_t index;
        size_t jsize;
        bool finish = 0;

        j = 0;
        if (*pend.begin() < *main.begin() && ++inserted)
            main.insert(main.begin(), *pend.begin());
        else
        {
            typename Cont::iterator max = main.begin();
            std::advance(max, inserted);
            max = std::lower_bound(main.begin(), max, *pend.begin());
            main.insert(max, *pend.begin());
        }
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
            maxIndexToSearch = jacobs[j - 1] * 2 + (jacobs[j] - jacobs[j - 1]) + inserted;
            if (maxIndexToSearch >= main.size() - 1 || j >= jsize)
                maxIndexToSearch = main.size() - 1;

            while (index >= jacobs[j - 1])
            {
                typename Cont::iterator itMaxSearch;
                itMaxSearch = main.begin();
                std::advance(itMaxSearch, maxIndexToSearch + 1);
                typename Cont::const_iterator itItem = pend.begin();
                std::advance(itItem, index);
                typename Cont::iterator itInsert = main.begin();
                itInsert = std::lower_bound(main.begin(), itMaxSearch, *itItem);
                main.insert(itInsert, *itItem);
                index--;
            }
            j++;
            if (finish)
                break;
        }
    }

    Cont fillMain(Cont &numbers, Cont &main, bool &straggler)
    {
        int i = 0;
        typename Cont::iterator it = numbers.begin();
        typename Cont::iterator itOdd = it;
        typename Cont::iterator end = numbers.end();
        itOdd++;

        while (it != end && itOdd != end)
        {
            if (it->n > itOdd->n)
                std::iter_swap(it, itOdd);
            main.push_back(*itOdd);
            main.back().pos = i; // index of the PAIR
            i++;
            std::advance(it, 2);
            std::advance(itOdd, 2);
        }
        if (it != end)
            straggler = true;
        return numbers;
    }

    void orderPend(const Cont &numbers, Cont &main, Cont &pend)
    {
        typename Cont::const_iterator numIt;
        typename Cont::iterator it = main.begin();
        typename Cont::iterator end = main.end();

        while (it != end)
        {
            numIt = numbers.begin();
            std::advance(numIt, (it->pos * 2));
            pend.push_back(*numIt);
            if (numIt->pos % 2 == 0)
                it->pos = it->pos * 2 + 1;
            else
                it->pos = it->pos * 2;
            it++;
        }
    }



    void log_container(const Cont &c, const std::string &label, bool pos = 0);
    std::ostream &log_container(std::ostream &o, const Cont &c, const std::string &label, bool pos = 0);
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
