#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		PmergeMe<std::vector<intM> > p(argc, argv);
		std::cout << p << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}
