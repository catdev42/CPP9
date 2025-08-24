#include <iostream>
#include <vector>

#include <climits>
#include <cstdlib>
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

void insert_or_reorganize_for_num(std::pair<int, int> element, std::vector<std::pair<int, int> > &numPairs, size_t index)
{
	// we will compare element with pair at index
	if (element.second >= numPairs[index].second)
		numPairs[index + 1] = element;
	else
	{
		numPairs[index + 1] = numPairs[index];
		if (index == 0)
		{
			numPairs[0] = element;
			return;
		}
		insert_or_reorganize_for_num(element, numPairs, index - 1);
	}
}

void recursive_insert_sort(std::vector<std::pair<int, int> > &numPairs, size_t index)
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

void create_main_and_pend(const std::vector<std::pair<int, int> > &sortedPairs, std::vector<int> &main, std::vector<int> &pend)
{
	for (size_t i = 0; i < sortedPairs.size(); i++)
	{
		main.push_back(sortedPairs[i].second);
		pend.push_back(sortedPairs[i].first);
	}
}

void insert_pend_into_main(std::vector<int> &main, std::vector<int> &pend, std::vector<size_t> jacobs)
{
	size_t j;
	size_t index;
	j = 0;
	main.insert(main.begin(), pend[0]); // insert before all numbers
	j+=2;
	while (j < jacobs.size() && jacobs[j] < pend.size())
	{
		index = jacobs[j] -1;
		size_t maxIndexToSearch = jacobs[j - 1] * 2 + (jacobs[j] - jacobs[j - 1]);
		while (index >= jacobs[j - 1])
		{
			size_t insertIndex = lower_bound_index(main, 0, maxIndexToSearch, pend[index]);
			main.insert(main.begin() + insertIndex, pend[index]);
			index--;
		}
		j++;
	}
	index = pend.size() - 1;
	size_t maxIndexToSearch = main.size();
	while (index >= jacobs[j - 1])
	{
		size_t insertIndex = lower_bound_index(main, 0, maxIndexToSearch, pend[index]);
		main.insert(main.begin() + insertIndex, pend[index]);
		index--;
	}
	;
}

int main(int argc, char **argv)
{
	long n1, n2;
	long straggler = -3000000000;
	size_t i;
	std::vector<std::pair<int, int> > numPairs;
	std::vector<int> main;
	std::vector<int> pend;

	static size_t jacobsArr[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};
	size_t jacobsthalSize = sizeof(jacobsArr) / sizeof(jacobsArr[0]);

	std::vector<size_t> jacobsthal(jacobsArr, jacobsArr + jacobsthalSize);

	char *endptr = NULL;

	if (argc < 2)
	{
		std::cerr << "Error: no input" << std::endl;
		return (1);
	}
	i = 1;
	while (i < static_cast<size_t>(argc))
	{
		n1 = strtol(argv[i], &endptr, 10);
		if (*endptr != 0 || n1 > INT_MAX)
		{
			std::cerr << "Error: not an int" << std::endl;
			return (1);
		}
		if (!argv[i + 1])
		{
			straggler = static_cast<int>(n1);
			break;
		}
		n2 = strtol(argv[i + 1], &endptr, 10);
		if (*endptr != 0 || n1 > INT_MAX)
		{
			std::cerr << "Error: not an int" << std::endl;
			return (1);
		}

		if (n2 > n1)
			numPairs.push_back(std::make_pair<int, int>(static_cast<int>(n1), static_cast<int>(n2)));
		else
			numPairs.push_back(std::make_pair<int, int>(static_cast<int>(n2), static_cast<int>(n1)));
		i += 2;
	}
	if (numPairs.size() > 1500)
		std::cerr << "Error: too many numbers, but here are the results anyway" << std::endl;

	/*
	Ford Johnson Merge Insert Sort Algorithm
	*/
	recursive_insert_sort(numPairs, numPairs.size() - 1);
	create_main_and_pend(numPairs, main, pend);
	insert_pend_into_main(main, pend, jacobsthal);
	if (straggler >= INT_MIN && straggler <= INT_MAX)
	{
		size_t insertIndex = lower_bound_index(main, 0, main.size(), straggler);
		main.insert(main.begin() + insertIndex, straggler);
	}

	/*
	Print
	*/
	for (i = 0; i < main.size(); ++i)
	{
		std::cout << main[i] << std::endl;
	}
}
