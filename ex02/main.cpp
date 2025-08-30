#include "PmergeMe.hpp"
#include <iomanip>

int main(int argc, char **argv)
{
	try
	{
		PmergeMe<std::vector<intM> > v(argc, argv);
		std::cout << v << std::endl;
		std::cout<< std::fixed << std::setprecision(7)<<"Time to process a range of 5 elements with std::vector : " << v.getElapsed() <<" us"<<std::endl;
		PmergeMe<std::list<intM> > l(argc, argv);
		// std::cout << l << std::endl;
		std::cout<<"Time to process a range of 5 elements with std::list : " << l.getElapsed() <<" us"<<std::endl;
		PmergeMe<std::deque<intM> > d(argc, argv);
		// std::cout << d << std::endl;
		std::cout<<"Time to process a range of 5 elements with std::deque : " << d.getElapsed() <<" us"<<std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}
