#include <iostream>
#include <vector>

#include <cstddef>

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

void insert_or_reorganize_for_num(std::pair<int, int> &element, std::vector<std::pair<int, int>> &numPairs, size_t index)
{
	// we will compare element with pair at index
	if (element.second >= numPairs[index].second)
		numPairs[index + 1] = element;
	else
	{
		numPairs[index + 1] = numPairs[index];
		if (index == 0)
			return;
		insert_or_reorganize_for_num(element, numPairs, index - 1);
	}
}

void recursive_insert_sort(std::vector<std::pair<int, int>> &numPairs, size_t index)
{
	if (index < 1)
		return;
	else
	{
		// launch n number of recursive sortings, one for each index
		recursive_insert_sort(numPairs, index - 1);
		// insertion algo
		insert_or_reorganize_for_num(numPairs[index], numPairs, index - 1);
	}
}

void create_main_and_pend(const std::vector<std::pair<int, int>> &unsortedPairs, std::vector<int> &main, std::vector<int> &pend)
{
	for (size_t i = 0; i < unsortedPairs.size(); i++)
	{
		main.push_back(unsortedPairs[i].second);
		pend.push_back(unsortedPairs[i].first);
	}
}

void insert_pend_into_main(std::vector<int> &main, std::vector<int> &pend, std::vector<int> jacobs)
{
}

int main(int argc, char **argv)
{
	long n1, n2;
	size_t i;
	std::vector<std::pair<int, int>> numPairs;
	std::vector<int> main;
	std::vector<int> pend;

	static size_t jacobsthal[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};
	size_t jacobsthalSize = sizeof(jacobsthal) / sizeof(jacobsthal[0]);

	std::vector<int> jacobsthalV(jacobsthal, jacobsthal + jacobsthalSize);

	char *endptr = NULL;

	if (argc < 2)
	{
		std::cerr << "Error: no input" << std::endl;
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		n1 = strtol(argv[i], &endptr, 0);
		if (*endptr != 0)
		{
			std::cerr << "Error: not a number" << std::endl;
			return (1);
		}
		if (argv[i + 1])
		{
			n2 = strtol(argv[i + 1], &endptr, 0);
			if (*endptr != 0)
			{
				std::cerr << "Error: not a number" << std::endl;
				return (1);
			}
		}
		if (n2 > n1)
			numPairs.push_back(std::make_pair<int, int>(n1, n2));
		else
			numPairs.push_back(std::make_pair<int, int>(n2, n1));
		i++;
	}
	if (numPairs.size() > 1500)
		std::cerr << "Error: too many numbers, but here are the results anyway" << std::endl;

	recursive_insert_sort(numPairs, i - 1 - 1); // adjust for argv[0] && len - 1 for last index
	create_main_and_pend(numPairs, main, pend);
	insert_pend_into_main(pend, main, jacobsthalV);
	// fordSort(unsortedNumberPairs); //TODO

	// PRINT
	for (i = 0; i < numPairs.size(); ++i)
	{
		std::cout << numPairs[i] << " ";
	}
	std::cout << std::endl;
}