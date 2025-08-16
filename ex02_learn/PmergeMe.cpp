/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:16:06 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/15 10:33:26 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

/*Getters*******************************/

std::vector<int> const&	PmergeMe::getVec(void) const
{
	return (this->_vec);
}

std::deque<int> const&	PmergeMe::getDeq(void) const
{
	return (this->_deq);
}

/***********************************/

// ################ CODE FOR VECTOR CONTAINER ####################

void	PmergeMe::parseInputVec(char** input)
{
	char*	endptr = NULL;
	long	tmp;
	int		num;
	while (*input && **input)
	{
		tmp = strtol(*input, &endptr, 10);
		if (*endptr)
			throw std::invalid_argument("Error: not a number.");
		if (tmp <= 0)
			throw std::invalid_argument("Error: accepts only strictly positive numbers.");
		if (tmp > INT_MAX)
			throw std::invalid_argument("Error: int overflow.");
		num = static_cast<int>(tmp);
		this->_vec.push_back(num);
		input++;
	}
	if (this->_vec.size() == 0)
		throw std::invalid_argument("Error: empty sequence."); // this should never happen
	return ;
}

void	PmergeMe::printVec(std::vector<int> const& vec)
{
	std::vector<int>::const_iterator	it;
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return ;
}

void	PmergeMe::sortVec(void)
{
	std::vector<int> vec = this->_vec; // create copy
	std::vector<int> indexes; // not useful in 1st call but needed in recurrence 

	PmergeMe::_recurSortVec(vec, indexes); // recursively sort copy
	this->_vec = vec; // replace original
	return ;
}

void	PmergeMe::_recurSortVec(std::vector<int>& vec, std::vector<int>& indexes)
{
	bool isFirstCall = indexes.empty();

	// Base case (length 1, do nothing)
	if (vec.size() == 1)
		return ;

	/* 	Virtually split into two equal-length segments (odd element unused if any)
		Virtually pair i-th element of each segment and make comparison
		Swap to have elements in first segment >= corresponding elements in second segment */
	
	std::vector<int>::iterator	it1 = vec.begin(); // points to beginning of first segment
	std::vector<int>::iterator	it2 = it1 + vec.size() / 2; // point to begin. of second segment
	std::vector<int>::iterator	itInd1; // same for index sequence
	std::vector<int>::iterator	itInd2;
	if (!isFirstCall)
	{
		itInd1 = indexes.begin(); // same for index sequence
		itInd2 = itInd1 + vec.size() / 2;
	}
	
	for (unsigned long j = 0; j < vec.size() / 2; j++)
	{
		if (*it2 > *it1)
		{
			std::iter_swap(it1, it2);
			if (!isFirstCall)
				std::iter_swap(itInd1, itInd2);
		}
		it1++;
		it2++;
		if (!isFirstCall)
		{
			itInd1++;
			itInd2++;
		}
	}
	
	// Split main and pend parts for both vec and Indexes
	std::vector<int> vecMain(vec.begin(), vec.begin() + vec.size() / 2);
	std::vector<int> vecPend(vec.begin() + vec.size() / 2, vec.end());
	std::vector<int> indMain;
	std::vector<int> indPend;
	if (!isFirstCall)
	{
		indMain.insert(indMain.end(), indexes.begin(), indexes.begin() + vec.size() / 2);
		indPend.insert(indPend.end(), indexes.begin() + vec.size() / 2, indexes.end());
	}
	
	//DEBUG
	if (VERBOSE && isFirstCall)
	{
		std::cout << "Splitted Vec into main chain and pend chain + pair swap:" << std::endl;
		PmergeMe::printVec(vecMain);
		PmergeMe::printVec(vecPend);
	}

	std::vector<int> subIndexes;
	for (unsigned long i = 0; i < vecMain.size(); i++)
		subIndexes.push_back(i);
	PmergeMe::_recurSortVec(vecMain, subIndexes);
	PmergeMe::_rearrangeVec(vecPend, subIndexes);
	if (!isFirstCall)
	{
		PmergeMe::_rearrangeVec(indMain, subIndexes);
		PmergeMe::_rearrangeVec(indPend, subIndexes);
	}

	// DEBUG
	if (VERBOSE && isFirstCall)
	{
		std::cout << "\nMain and pend and after recursive sort:" << std::endl;
		PmergeMe::printVec(vecMain);
		PmergeMe::printVec(vecPend);
	}
	PmergeMe::_binaryInsertVec(vecMain, vecPend, indMain, indPend);
	vec = vecMain;
	indexes = indMain;

	return ;	
}

void	PmergeMe::_rearrangeVec(std::vector<int>& vec, std::vector<int>& indexes)
{
	std::vector<int> vecCopy = vec;
	for (unsigned long i = 0; i < indexes.size(); i++)
		vec[i] = vecCopy[indexes[i]];
	return ;
}

// Binary insert with jacobsthal sequence
void	PmergeMe::_binaryInsertVec(std::vector<int>& vecMain, std::vector<int>& vecPend,
	std::vector<int>& indMain, std::vector<int>& indPend)
{
	bool isFirstCall = indMain.empty();

	std::vector<unsigned long>	jacob;
	std::vector<long>			maxChainSize; // to insert into
	unsigned long				jacobPrev = 1;
	long						insertSize; // size of chain to insert into
	std::vector<int>::iterator	it; // position before which to insert
	
	jacob.push_back(1);
	maxChainSize.push_back(1);
	// Generate needed Jacobsthal sequence and maxChainSize
	while (jacob.back() < vecPend.size())
	{
		jacob.push_back(jacob.back() + 2 * jacobPrev);
		jacobPrev = *(jacob.end() - 2);
		maxChainSize.push_back((maxChainSize.back() + 1) * 2 - 1); //2^n - 1
	}

	for (unsigned long j = 0; j < jacob.size(); j++)
	{
		jacobPrev = (jacob[j] == 1) ? 0 : jacob[j - 1];
		for (unsigned long i = jacob[j]; i > jacobPrev; i--)
		{
			if (i > vecPend.size())
				continue ;
			
			insertSize = std::min(vecMain.end() - vecMain.begin(), maxChainSize[j]);
			if (VERBOSE && isFirstCall)	
				std::cout << "\nInserting pend element " <<  vecPend[i - 1] 
					<< " into sub main chain of length " << insertSize << ":" << std::endl;
			
			// Very first insert need no comparison
			if (i == 1)
			{
				it = vecMain.begin();	
			}
			else // Lower_bound performs binary search
			{
				it = std::lower_bound(vecMain.begin(), 
					vecMain.begin() + insertSize, vecPend[i - 1]); // need 2nd it to pass bound
			}

			if (!isFirstCall)
				indMain.insert(indMain.begin() + std::distance(vecMain.begin(), it), indPend[i - 1]);
			vecMain.insert(it, vecPend[i - 1]);
			
			if (VERBOSE && isFirstCall)
			{
				PmergeMe::printVec(vecMain);
				PmergeMe::printVec(vecPend);
			}
		}
	}
	return ;
}

/***********************************/

// ################ CODE FOR DEQUE CONTAINER ####################

void	PmergeMe::parseInputDeq(char** input)
{
	char*	endptr = NULL;
	long	tmp;
	int		num;
	while (*input && **input)
	{
		tmp = strtol(*input, &endptr, 10);
		if (*endptr)
			throw std::invalid_argument("Error: not a number.");
		if (tmp <= 0)
			throw std::invalid_argument("Error: accepts only strictly positive numbers.");
		if (tmp > INT_MAX)
			throw std::invalid_argument("Error: int overflow.");
		num = static_cast<int>(tmp);
		this->_deq.push_back(num);
		input++;
	}
	if (this->_deq.size() == 0)
		throw std::invalid_argument("Error: empty sequence."); // this should never happen
	return ;
}

void	PmergeMe::printDeq(std::deque<int> const& deq)
{
	std::deque<int>::const_iterator	it;
	for (it = deq.begin(); it != deq.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return ;
}

void	PmergeMe::sortDeq(void)
{
	std::deque<int> deq = this->_deq; // create copy
	std::deque<int> indexes; // not useful in 1st call but needed in recurrence 

	PmergeMe::_recurSortDeq(deq, indexes); // recursively sort copy
	this->_deq = deq; // replace original
	return ;
}

void	PmergeMe::_recurSortDeq(std::deque<int>& deq, std::deque<int>& indexes)
{
	bool isFirstCall = indexes.empty();

	// Base case (length 1, do nothing)
	if (deq.size() == 1)
		return ;

	/* 	Virtually split into two equal-length segments (odd element unused if any)
		Virtually pair i-th element of each segment and make comparison
		Swap to have elements in first segment >= corresponding elements in second segment */
	
	std::deque<int>::iterator	it1 = deq.begin(); // points to beginning of first segment
	std::deque<int>::iterator	it2 = it1 + deq.size() / 2; // point to begin. of second segment
	std::deque<int>::iterator	itInd1; // same for index sequence
	std::deque<int>::iterator	itInd2;
	if (!isFirstCall)
	{
		itInd1 = indexes.begin(); // same for index sequence
		itInd2 = itInd1 + deq.size() / 2;
	}
	
	for (unsigned long j = 0; j < deq.size() / 2; j++)
	{
		if (*it2 > *it1)
		{
			std::iter_swap(it1, it2);
			if (!isFirstCall)
				std::iter_swap(itInd1, itInd2);
		}
		it1++;
		it2++;
		if (!isFirstCall)
		{
			itInd1++;
			itInd2++;
		}
	}
	
	// Split main and pend parts for both deq and Indexes
	std::deque<int> deqMain(deq.begin(), deq.begin() + deq.size() / 2);
	std::deque<int> deqPend(deq.begin() + deq.size() / 2, deq.end());
	std::deque<int> indMain;
	std::deque<int> indPend;
	if (!isFirstCall)
	{
		indMain.insert(indMain.end(), indexes.begin(), indexes.begin() + deq.size() / 2);
		indPend.insert(indPend.end(), indexes.begin() + deq.size() / 2, indexes.end());
	}
	
	//DEBUG
	if (VERBOSE && isFirstCall)
	{
		std::cout << "Splitted Deq into main chain and pend chain + pair swap:" << std::endl;
		PmergeMe::printDeq(deqMain);
		PmergeMe::printDeq(deqPend);
	}

	std::deque<int> subIndexes;
	for (unsigned long i = 0; i < deqMain.size(); i++)
		subIndexes.push_back(i);
	PmergeMe::_recurSortDeq(deqMain, subIndexes);
	PmergeMe::_rearrangeDeq(deqPend, subIndexes);
	if (!isFirstCall)
	{
		PmergeMe::_rearrangeDeq(indMain, subIndexes);
		PmergeMe::_rearrangeDeq(indPend, subIndexes);
	}

	// DEBUG
	if (VERBOSE && isFirstCall)
	{
		std::cout << "\nMain and pend and after recursive sort:" << std::endl;
		PmergeMe::printDeq(deqMain);
		PmergeMe::printDeq(deqPend);
	}
	PmergeMe::_binaryInsertDeq(deqMain, deqPend, indMain, indPend);
	deq = deqMain;
	indexes = indMain;

	return ;	
}

void	PmergeMe::_rearrangeDeq(std::deque<int>& deq, std::deque<int>& indexes)
{
	std::deque<int> deqCopy = deq;
	for (unsigned long i = 0; i < indexes.size(); i++)
		deq[i] = deqCopy[indexes[i]];
	return ;
}

// Binary insert with jacobsthal sequence
void	PmergeMe::_binaryInsertDeq(std::deque<int>& deqMain, std::deque<int>& deqPend,
	std::deque<int>& indMain, std::deque<int>& indPend)
{
	bool isFirstCall = indMain.empty();

	std::deque<unsigned long>	jacob;
	std::deque<long>			maxChainSize; // to insert into
	unsigned long				jacobPrev = 1;
	long						insertSize; // size of chain to insert into
	std::deque<int>::iterator	it; // position before which to insert
	
	jacob.push_back(1);
	maxChainSize.push_back(1);
	// Generate needed Jacobsthal sequence and maxChainSize
	while (jacob.back() < deqPend.size())
	{
		jacob.push_back(jacob.back() + 2 * jacobPrev);
		jacobPrev = *(jacob.end() - 2);
		maxChainSize.push_back((maxChainSize.back() + 1) * 2 - 1); //2^n - 1
	}

	for (unsigned long j = 0; j < jacob.size(); j++)
	{
		jacobPrev = (jacob[j] == 1) ? 0 : jacob[j - 1];
		for (unsigned long i = jacob[j]; i > jacobPrev; i--)
		{
			if (i > deqPend.size())
				continue ;
			
			insertSize = std::min(deqMain.end() - deqMain.begin(), maxChainSize[j]);
			if (VERBOSE && isFirstCall)	
				std::cout << "\nInserting pend element " <<  deqPend[i - 1] 
					<< " into sub main chain of length " << insertSize << ":" << std::endl;
			
			// Very first insert need no comparison
			if (i == 1)
			{
				it = deqMain.begin();	
			}
			else // Lower_bound performs binary search
			{
				it = std::lower_bound(deqMain.begin(), 
					deqMain.begin() + insertSize, deqPend[i - 1]); // need 2nd it to pass bound
			}

			if (!isFirstCall)
				indMain.insert(indMain.begin() + std::distance(deqMain.begin(), it), indPend[i - 1]);
			deqMain.insert(it, deqPend[i - 1]);
			
			if (VERBOSE && isFirstCall)
			{
				PmergeMe::printDeq(deqMain);
				PmergeMe::printDeq(deqPend);
			}
		}
	}
	return ;
}


