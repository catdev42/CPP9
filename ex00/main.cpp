#include <iostream>
#include "BitcoinExchange.hpp"

#include <iostream>

#include <fstream>
#include <sstream>
#include <exception>

#include <ctime>

int main(int argc, char **argv)
{
	std::string line;

	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	std::ifstream f(argv[1]);
	if (!f.good())
	{
		if (!f.good())
			std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	std::getline(f, line);

	try
	{
		BitcoinExchange btc("data.csv");
		while (getline(f, line))
		{
			try
			{
				std::string date;
				char delim;
				int amountBTC;
				std::istringstream lineStream(line);
				if (!(lineStream >> date >> delim >> amountBTC))
				{
					std::cerr << "Error: bad input => " << line << std::endl;
					continue;
				}
				std::cout << btc.executeLine(date, amountBTC) << std::endl;
			}
			catch (BitcoinExchange::InputError &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}