#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

/*SORT*/


template <typename Cont>
Cont PmergeMe<Cont>::small_sort(Cont &numbers)
{
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
	return numbers;
}


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
bool PmergeMe<Cont>::is_sorted_by_n(const Cont &c) const
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
