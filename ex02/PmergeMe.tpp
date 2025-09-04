#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

/* PUBLIC FUNCTION */
template <typename Cont>
Cont PmergeMe<Cont>::sort(int argc, char **argv)
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

/***********/
/*  SORT   */
/***********/
/* PRIVATE */

template <typename Cont>
Cont PmergeMe<Cont>::sort(Cont &numbers, size_t &inserted)
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

template <typename Cont>
void PmergeMe<Cont>::insert(Cont &main, const Cont &pend, size_t &inserted)
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
		maxIndexToSearch = jacobs[j - 1] * 2 + (jacobs[j] - jacobs[j - 1]);
		if (maxIndexToSearch >= main.size() - 1 || j >= jsize)
			maxIndexToSearch = main.size() - 1;

		typename Cont::iterator itMaxSearch = main.begin();
		typename Cont::const_iterator itItem = pend.begin();
		typename Cont::iterator itInsert = main.begin();
		std::advance(itItem, index);
		std::advance(itMaxSearch, maxIndexToSearch + 1);
		while (index >= jacobs[j - 1])
		{
			if (is_same<Cont, std::list<intM>>::value)
				itMaxSearch--;
			else
			{
				itMaxSearch = main.begin();
				std::advance(itMaxSearch, maxIndexToSearch);
			}
			itInsert = std::lower_bound(main.begin(), itMaxSearch, *itItem);
			main.insert(itInsert, *itItem);
			itItem--;
			index--;
		}
		j++;
		if (finish)
			break;
	}
}

template <typename Cont>
Cont PmergeMe<Cont>::fillMain(Cont &numbers, Cont &main, bool &straggler)
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

template <typename Cont>
void PmergeMe<Cont>::orderPend(const Cont &numbers, Cont &main, Cont &pend)
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

/***********/
/* HELPERS */
/***********/

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
/*
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
*/

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
