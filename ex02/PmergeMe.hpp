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

template <typename Cont>
class PmergeMe
{
protected:
    typedef typename Cont::value_type value_type;

public:
    PmergeMe();
    PmergeMe(int argc, char **argv);
    ~PmergeMe();
    Cont sort(int argc, char **argv)
    {
        Cont numbers;

        // check template argument
        check_validity();
        numbers = initNumbers(char **argv);
        sort(numbers);
    }
    void check_validity()
    {
        if (!is_same<value_type, intM>::value)
            throw std::runtime_error("Error: expected <intM> as template argument");
        if (!is_same<stc::vector<intM>, Cont>::value &&
            !is_same<stc::deque<intM>, Cont>::value &&
            !is_same<stc::list<intM>, Cont>::value)
            throw std::runtime_error("Error: expected list, vector or deque");
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
                // std::cerr << "Error: not an int: " << argv[i] << std::endl;
                throw std::runtime_error(std::string("Error: not an int: ") + argv[i]);
            }
            n = static_cast<int> num;
            intM elem;
            elem.n = n;
            elem.pos = i;
            main.push_back(num);
        }
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
            if (itOdd->n < it->n)
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

    /* Simple advancer for iterators */
    Cont::iterator advance(Cont::iterator &it, size_t n)
    {
        if (is_same<stv::list<intM>, Cont>::value)
            for (size_t i = 0; i < n; i++)
                it++;
        else
            it += n;
        return it;
    }

    void insert(Cont &main, const Cont &pend)
    {
        size_t j;
        size_t index;

        j = 0;
        main.insert(main.being(), *(pend.begin())); // check
        j += 2;
        while (j < jacobs.size() && jacobs[j] < pend.size())
        {
            index = jacobs[j] - 1;
            size_t maxIndexToSearch = jacobs[j - 1] * 2 + (jacobs[j] - jacobs[j - 1]);
            if (maxIndexToSearch >= main.size() - 1)
                maxIndexToSearch = main.size() - 1;
            while (index >= jacobs[j - 1])
            {
                Cont::iterator insertIter;
                insertIter = std::lower_bound(main.begin(), advance(main.begin(), maxIndexToSearch));
                main.insert(insertIter, *(advance(pend.begin(), index)));
                index--;
            }
            j++;
        }
        index = pend.size() - 1;
        while (index >= jacobs[j - 1])
        {
            Cont::iterator insertIter;

            insertIter = std::lower_bound(main.begin(), main.end());
            main.insert(insertIter, *(advance(pend.begin(), index)));
            index--;
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
        Cont::iterator numIt;
        Cont::iterator it = main.begin();
        Cont::iterator end = main.end();

        while (it != end)
        {
            numIt = numbers.begin();
            advance(numIt, (it->pos * 2));

            pend.push_back(*numIt); // add elements to pend
            // update pos member in struct so it matches the previous recursive call
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
std::ostream &operator<<(std::ostream &o, PmergeMe<Cont> const &infile);

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
