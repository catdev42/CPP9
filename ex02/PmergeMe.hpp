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

#ifndef COLOR
#define COLOR
#define GREY "\033[0;30m"
#define RESET "\033[0m"
#endif

typedef struct intInfo
{
    int n;
    int pos;
    bool operator<(const struct intInfo &a) const { return this->n < a.n; }
    bool operator>(const struct intInfo &a) const { return this->n > a.n; }

} intM;

// TODO: time, printing outputs
/*
TIME:
startTime = std::clock(NULL);
endTime = std::time(NULL);
double elapsed = double(endTime - startTime) / CLOCKS_PER_SEC;
*/

/**
 * templated class for Ford Johnson sorting algorithm
 */
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

        startTime = std::clock();
        check_validity();
        numbers = initNumbers(argc, argv);
        unsorted = numbers;
        sort(numbers);
        endTime = std::clock();
        elapsed = double(endTime - startTime) / CLOCKS_PER_SEC;

        return this->sorted;
    }

    Cont initNumbers(int argc, char **argv)
    {
        Cont main;

        for (int i = 1; i < argc; i++)
        {
            long num;
            int n;
            std::stringstream ss;
            ss << argv[i];
            if (!(ss >> num) || num > INT_MAX || num < INT_MIN)
            {
                // std::cerr << "Error: not an int: " << argv[i] << std::endl;
                throw std::runtime_error(std::string("Error: not an int: ") + argv[i]);
            }
            n = static_cast<int>(num);
            intM elem;
            elem.n = n;
            elem.pos = i - 1;
            main.push_back(elem);
        }
        numAmount = main.size();
        return main;
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
        main = sort(main);
        orderPend(numbers, main, pend);
        insert(main, pend);
        if (strag)
        {
            typename Cont::iterator pos = std::lower_bound(main.begin(), main.end(), straggler);
            main.insert(pos, straggler);
        }
        if (main.size() == numAmount)
            sorted = main;
        return main;
    }

    /*gives new indexes to main made of biggen numbers*/
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
            it++;
            it++;
            itOdd++;
            itOdd++;
        }
        if (it != end)
            straggler = true;
    }

    void insert(Cont &main, const Cont &pend)
    {
        size_t j;
        size_t index;
        size_t jsize;
        bool finish = 0;

        j = 0;
        main.insert(main.begin(), *(pend.begin())); // check
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
            maxIndexToSearch = jacobs[j - 1] * 2 + (jacobs[j] - jacobs[j - 1]);
            if (maxIndexToSearch >= main.size() - 1 || j > jsize)
                maxIndexToSearch = main.size() - 1;

            while (index >= jacobs[j - 1])
            {
                typename Cont::iterator itMaxSearch;
                itMaxSearch = main.begin();
                std::advance(itMaxSearch, maxIndexToSearch);
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

    /**
     * main pos indexes:  2 0 3 1 4 5
     * need to restore the pos indexes to match original array that included all nums
     * main pos indexes: 5 1 7 3 9 11
     * find pend elements: 4 0 6 2 8 10
     * */
    void orderPend(const Cont &numbers, Cont &main, Cont &pend)
    {
        typename Cont::const_iterator numIt;
        typename Cont::iterator it = main.begin();
        typename Cont::iterator end = main.end();

        while (it != end)
        {
            numIt = numbers.begin();
            std::advance(numIt, (it->pos * 2));
            pend.push_back(*numIt);    // add elements to pend
            it->pos = it->pos * 2 + 1; // restoring original positions in main to match prev recursive call
            it++;
        }
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

    void check_validity()
    {
        if (!is_same<value_type, intM>::value)
            throw std::runtime_error("Error: expected <intM> as template argument");
        if (!is_same<std::vector<intM>, Cont>::value &&
            !is_same<std::deque<intM>, Cont>::value &&
            !is_same<std::list<intM>, Cont>::value)
            throw std::runtime_error("Error: expected list, vector or deque");
    }

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

/*
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
*/

#endif

/*
//Personal Implementation of lower bound eindex search
size_t lower_bound_index(const std::vector<int> &vec, size_t first, size_t last, int val)
{
    size_t count = last - first; // the number of things
    while (count > 0)			 // the array we are working with is 0 size
    {
        size_t step = count / 2;   // half of things
        size_t mid = first + step; // index of the center

        if (vec[mid] < val)
        {
            first = mid + 1; // we get rid of mid and search above it
            count = count - step - 1;
            count_compare++;
        }
        else // if (vec[mid] >= val)
        {
            count = step;
            count_compare++;
        }
    }
    return first;
}
*/
