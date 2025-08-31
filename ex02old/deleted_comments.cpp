
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
