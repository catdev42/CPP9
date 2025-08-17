#include <iostream>
#include <vector>

\
//getting a bit confused how to actually do this

//i need to start with the current jacobsthal number and go back down to the previous (smaller) one
//i need to insert them into the main array using binary search

void insertPendIntoMain(const std::vector<std::pair<int, int>> &pend, std::vector<int> &main, int *jacobsthal)
{
	main.insert(main.begin(), pend[0].first);


	std::vector<int>::iterator maxi = std::find(main.begin(), main.end(), );

}

void fordSort(std::vector<int> &numbers)
{

	std::vector<std::pair<int, int>> pend;
	std::vector<int> main;

	int i = 0;
	int straggler = -1;
	static int jacobsthal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365};

	if (numbers.size() == 1)
		return;
	if (numbers.size() == 2)
	{
		if (numbers[0] > numbers[1])
			std::swap(numbers[0], numbers[1]);
		return;
	}

	while (i + 1 < numbers.size())
	{
		if (numbers[i] > numbers[i + 1])
		{
			pend.push_back(std::make_pair(numbers[i + 1], numbers[i]));
			main.push_back(numbers[i]);
		}
		else
		{
			pend.push_back(std::make_pair(numbers[i], numbers[i + 1]));
			main.push_back(numbers[i + 1]);
		}
		i += 2;
	}
	if (i < numbers.size())
		straggler = numbers[i];

	fordSort(main);
	insertPendIntoMain(pend, main, jacobsthal);
	numbers = main;
}

// void fordSort(std::vector<std::pair<int, int>> myPairs, std::vector<int> sorted)
// {
// 	std::vector<std::pair<int, int>> pend;
// 	std::vector<std::pair<int, int>> main;
// 	int temp;

// 	// sort inside the pairs
// 	for (std::vector<std::pair<int, int>>::iterator it = myPairs.begin(); it != myPairs.end(); ++it)
// 	{

// 		if (it->first > it->second)
// 		{
// 			temp = it->second;
// 			it->second = it->first;
// 			it->first = temp;
// 		}
// 		int newMainFirst = it->second;
// 		int newPendFirst = it->first;
// 		++it;
// 		if (it->first > it->second)
// 		{
// 			temp = it->second;
// 			it->second = it->first;
// 			it->first = temp;
// 		}
// 		main.push_back(std::make_pair(newMainFirst, it->second));
// 		pend.push_back(std::make_pair(newPendFirst, it->first));
// 		fordSort(main, sorted);

// 		insertPendIntoSorted(pend)

// 	}

// 	for (std::vector<std::pair<int, int>>::iterator it = myPairs.begin(); it != myPairs.end(); ++it)
// 	{
// 	}
// }

int main(int argc, char **argv)
{
	long n;
	int i;
	std::vector<std::pair<int, int>> myPairs;
	std::vector<int> unsortedNumbers;
	std::vector<int> sorted;
	char *endptr = NULL;

	if (argc < 2)
	{
		std::cerr << "Error: no input" << std::endl;
		return (1);
	}
	i = 1;
	n = strtol(argv[i], &endptr, 0);

	if (*endptr != 0)
	{
		std::cerr << "Error: not a number" << std::endl;
		return (1);
	}
	i++;
	unsortedNumbers.push_back(n);
	// TODO check that not more than max int
	while (argv[i])
	{
		n = strtol(argv[i], &endptr, 0);
		unsortedNumbers.push_back(static_cast<int>(n));
		i++;
	}
	i = 0;
	while (i < unsortedNumbers.size())
	{
		myPairs.push_back(std::make_pair(unsortedNumbers[i], unsortedNumbers[i + 1]));
		i += 2;
	}
	fordSort(myPairs, sorted);

	// try
	// {
	// 	result = RPN::processRPN(str);
	// 	std::cout << result << std::endl;
	// }
	// catch (std::exception &e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }
}
