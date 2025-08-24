#include <iostream>
#include <vector>

#include <cstddef>

// getting a bit confused how to actually do this

// i need to start with the current jacobsthal number and go back down to the previous (smaller) one
// i need to insert them into the main array using binary search

// need condition for inserting at the very end or the very beginning

// 0 1 2 3 4 5(6)

// last is one past the end of the search range
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
		}
		else // if (vec[mid] >= val)
		{
			count = step;
		}
	}
	return first;
}

insert_pend_into_main()

	void fordSort(std::vector<int> &numbersOg)
{
	std::vector<int> main;
	std::vector<int> numbers;

	numbers = numbersOg;
	size_t i = 0;
	int straggler = -1;
	static size_t jacobsthal[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};
	static int jaclen = 13;

	if (numbers.size() == 1)
		return;
	if (numbers.size() == 2)
	{
		if (numbers[0] > numbers[1])
			std::swap(numbers[0], numbers[1]);
		return;
	}
	// organize inside pairs
	while (i + 1 < numbers.size())
	{
		if (numbers[i] < numbers[i + 1])
			std::swap(numbers[i], numbers[i + 1]);
		main.push_back(numbers[i]);
		i += 2;
	}

	if (i < numbers.size())
		straggler = numbers[i];

	fordSort(main);

	std::vector<int> pend;
	// iterate through the ordered "main"
	// fill the pend vector with appropriate pairs
	// match the order of "pend" to be the same as main
	for (i = 0; i < main.size(); i++)
	{
		for (size_t j = 0; j + 1 < numbers.size(); j += 2)
			if (numbers[j] == main[i])
			{
				pend.push_back(numbers[j + 1]);
				numbers[j] = -1;
				break;
			}
	}
	insertPendIntoMain(pend, main, jacobsthal, jaclen);
	if (straggler > 0)
		binarySearchInsert(main, main.size() - 1, straggler);
	numbersOg = main;
}

int main(int argc, char **argv)
{
	long n;
	size_t i;
	// std::vector<std::pair<int, int>> myPairs;
	std::vector<int> unsortedNumbers;
	std::vector<int> sorted;
	char *endptr = NULL;

	if (argc < 2)
	{
		std::cerr << "Error: no input" << std::endl;
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		n = strtol(argv[i], &endptr, 0);
		if (*endptr != 0)
		{
			std::cerr << "Error: not a number" << std::endl;
			return (1);
		}
		unsortedNumbers.push_back(static_cast<int>(n));
		i++;
	}
	if (unsortedNumbers.size() > 3000)
		std::cerr << "Error: too many numbers, but here are the results anyway" << std::endl;
	fordSort(unsortedNumbers);

	// PRINT
	for (i = 0; i < unsortedNumbers.size(); ++i)
	{
		std::cout << unsortedNumbers[i] << " ";
	}
	std::cout << std::endl;
}

// try
// {
// 	result = RPN::processRPN(str);
// 	std::cout << result << std::endl;
// }
// catch (std::exception &e)
// {
// 	std::cout << e.what() << std::endl;
// }

// void binarySearchInsert(std::vector<int> &main, size_t endIndex, int num)
// {
// 	size_t mIndex;
// 	size_t sIndex;

// 	sIndex = 0;
// 	if (main[endIndex] < num)
// 	{
// 		main.insert(main.end(), num);
// 		return;
// 	}
// 	std::lower_bound(main.begin() + endIndex, main.begin() + (endIndex * 2), num);
// 	while (true)
// 	{
// 		mIndex = (endIndex + sIndex) / 2;
// 		if ((main[mIndex] > num && main[mIndex - 1] < num) || endIndex == 0)
// 		{
// 			main.insert(main.begin() + mIndex, num);
// 			break;
// 		}
// 		if (sIndex == endIndex || sIndex + 1 == endIndex) // delete if not triggered
// 		{
// 			std::cerr << "Error: something went wrong, cannot insert";
// 			exit(1);
// 		}
// 		if (num < main[mIndex])
// 			endIndex = mIndex;
// 		else
// 			sIndex = mIndex;
// 	}
// }

/*
void insertPendIntoMain(const std::vector<int> &pend, std::vector<int> &main, size_t *jacobsthal, size_t jaclen)
{
	size_t iPend;	// index in pend
	size_t iJacobs; // index in jacobs
	size_t last;
	bool isFinished;
	size_t insertIndex;
	std::vector<int> ogMain = main;

	isFinished = 0;
	iJacobs = 0;
	iPend = 0;

	main.insert(main.begin(), pend[0]);
	iJacobs++;
	while (iJacobs < jaclen)
	{
		if (jacobsthal[iJacobs] > main.size())
		{
			iPend = pend.size() - 1;
			isFinished = 1;
			last = main.size();
		}
		else
		{
			iPend = jacobsthal[iJacobs] - 1;
			last = jacobsthal[iJacobs];
		}

		while (iPend >= jacobsthal[iJacobs - 1])
		{

			insertIndex = lower_bound_index(main, 0, last, pend[iPend]);
			main.insert(main.begin() + insertIndex, pend[iPend]);
			iPend--;
		}

		if (isFinished)
			break;
		iJacobs++;
	}
}
	*/