#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

/*SORT*/

/*
 * main pos indexes:  2 0 3 1 4 5
 * need to restore the main pos indexes to match og nums array
 * main pos indexes: 5 1 7 3 9 11 find pend elements: 4 0 6 2 8 10
 * */
// template <typename Cont>
// void PmergeMe<Cont>::orderPend(const Cont &numbers, Cont &main, Cont &pend)
// {
// 	typename Cont::const_iterator numIt;
// 	typename Cont::iterator it = main.begin();
// 	typename Cont::iterator end = main.end();

// 	while (it != end)
// 	{
// 		numIt = numbers.begin();
// 		std::advance(numIt, (it->pos * 2));
// 		pend.push_back(*numIt);	   // add elements to pend
// 		it->pos = it->pos * 2 + 1; // restoring original positions in main to match prev recursive call
// 		it++;
// 	}
// }

/* HELPERS */

template <typename Cont>
Cont PmergeMe<Cont>::initNumbers(int argc, char **argv)
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

template <typename Cont>
void PmergeMe<Cont>::log_container(const Cont &c, const std::string &label, bool pos)
{
	debug_log << label << ": ";
	for (typename Cont::const_iterator it = c.begin(); it != c.end(); ++it)
	{
		debug_log << it->n;
		if (pos)
			debug_log << "pos[" << it->pos << "]";
		debug_log << " ";
	}
	debug_log << std::endl;
}

template <typename Cont>
std::ostream &PmergeMe<Cont>::log_container(std::ostream &o, const Cont &c, const std::string &label, bool pos)
{
	o << label << ": ";
	for (typename Cont::const_iterator it = c.begin(); it != c.end(); ++it)
	{
		o << it->n;
		if (pos)
			o << "pos[" << it->pos << "]";
		o << " ";
	}
	o << std::endl;
	return o;
}

template <typename Cont>
bool PmergeMe<Cont>::is_sorted_by_n(const Cont &c)
{
	if (c.empty())
		return true;
	typename Cont::const_iterator prev = c.begin();
	typename Cont::const_iterator curr = prev;
	++curr;
	while (curr != c.end())
	{
		if (curr->n < prev->n)
			return false;
		++prev;
		++curr;
	}
	return true;
}

template <typename Cont>
void PmergeMe<Cont>::check_validity()
{
	if (!is_same<value_type, intM>::value)
		throw std::runtime_error("Error: expected <intM> as template argument");
	if (!is_same<std::vector<intM>, Cont>::value &&
		!is_same<std::deque<intM>, Cont>::value &&
		!is_same<std::list<intM>, Cont>::value)
		throw std::runtime_error("Error: expected list, vector or deque");
}

#endif

// template <typename Cont>
// int PmergeMe<Cont>::stragCount = 0;

/*
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
*/
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
