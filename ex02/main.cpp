#include "PmergeMe.hpp"
#include <iomanip>
// error set: 15 16 2 10 8 9 11 7 3 14 12 5 13 6 4 1
// error set: 12 5 16 15 3 6 2 7 10 4 1 13 14 11 8 9
// error set: 16 15 3 9 7 6 12 8 1 11 10 4 13 14 2 5
/*
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
*/
int main(int argc, char **argv)
{
	try
	{
		PmergeMe<std::vector<intM>> v(argc, argv);
		std::cout << std::fixed << std::setprecision(8);
		std::cout << v << std::endl;
		std::cout << "Time to process a range of " << argc - 1
				  << " elements with std::vector : " << v.getElapsed() << " s" << std::endl;
		PmergeMe<std::list<intM>> l(argc, argv);
		std::cout << "Time to process a range of " << argc - 1
				  << " elements with std::list : " << l.getElapsed() << " s" << std::endl;
		PmergeMe<std::deque<intM>> d(argc, argv);
		std::cout << "Time to process a range of " << argc - 1
				  << " elements with std::deque : " << d.getElapsed() << " s" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}
