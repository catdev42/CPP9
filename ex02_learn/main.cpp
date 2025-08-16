/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:20:31 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/15 10:36:07 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>

int main(int ac, char** av)
{
	if (ac == 1 || *av[1] == 0)
	{
		std::cout << "Error: empty input sequence." << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		PmergeMe pme;
		
		clock_t beginVec = std::clock();
		pme.parseInputVec(++av);
		std::cout << "Before: ";
		PmergeMe::printVec(pme.getVec());
		pme.sortVec();
		std::cout << "After: ";
		PmergeMe::printVec(pme.getVec());
  		clock_t endVec = clock();
  		double elapsed_usecs = double(endVec - beginVec) / CLOCKS_PER_SEC * 1000000;
		std::cout << "Time to process a range of " << ac - 1 
		<< " elements with std::vector: " << elapsed_usecs << " us" << std::endl;
	
		clock_t beginDeq = std::clock();
		pme.parseInputDeq(av);
		//std::cout << "Before: ";
		//PmergeMe::printDeq(pme.getDeq());
		pme.sortDeq();
		//std::cout << "After: ";
		//PmergeMe::printDeq(pme.getDeq());
  		clock_t endDeq = clock();
  		elapsed_usecs = double(endDeq - beginDeq) / CLOCKS_PER_SEC * 1000000;
		std::cout << "Time to process a range of " << ac - 1 
		<< " elements with std::deque: " << elapsed_usecs << " us" << std::endl;
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
