#include "BitcoinExchange.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <climits>

/********************************************/
/********************************************/
/******        MEMBER FUNCTIONS        ******/

void BitcoinExchange::updateDataBase(const std::string &db)
{
    std::string line;
    std::string key;
    double priceBTC;

    std::fstream f(db.c_str());

    if (!f.good())
        throw BitcoinExchange::InputError("Error: cannot read database.");

    getline(f, line);

    while (getline(f, line))
    {
        std::istringstream lineStream(line);
        if (getline(lineStream, key, ',') && lineStream >> priceBTC)
            data[key] = priceBTC;
    }
}

double BitcoinExchange::executeLine(const std::string &date, double amountBTC)
{
    if (amountBTC < 0)
        throw InputError("Error: not a positive number.");
    if (!extractDate(date))
        throw InputError("Error: not a valid date.");
    if (amountBTC > INT_MAX)
        throw InputError("Error: too large a number.");

    std::map<std::string, double>::iterator it;
    it = data.lower_bound(date);
    if (it == data.end() || (it->first > date && it != data.begin()))
        it = it--;

    if (it != data.end())
        return (amountBTC * it->second);

    throw InputError("Error: date predates Bitcoin.");
    return 0;
}

/**
 * struct tm takes in these cariables:
 * day from 1 to 31,
 * month from 0 to 11 and
 * year in how many years after 1900
 * + is daylight savings time variable
 * then this struct can be converted to time_t (time since epoch)
 * then this can be converted back to tm with function localtime(<time_t>)
 * IF these are the same, then the date is valid
 *
 * function expects the string in format dd-mm-yyyy
 */
// bool BitcoinExchange::extractDate(const std::string &s, int &y, int &m, int &d)
bool BitcoinExchange::extractDate(const std::string &s)
{
    int y;
    int m;
    int d;
    std::istringstream is(s);
    char delimiter;
    if (is >> y >> delimiter >> m >> delimiter >> d)
    {
        struct tm t = {};
        t.tm_mday = d;
        t.tm_mon = m - 1;
        t.tm_year = y - 1900;
        t.tm_isdst = -1;
        time_t when = mktime(&t);
        const struct tm *norm = localtime(&when);
        return (norm->tm_mday == d &&
                norm->tm_mon == m - 1 &&
                norm->tm_year == y - 1900);
    }
    return false;
}

/********************************************/
/********************************************/
/******          CONSTRUCTORS          ******/

BitcoinExchange::BitcoinExchange(const std::string &db)
{
    std::cout << GREY << "BitcoinExchange database constructor" << RESET << std::endl;
    updateDataBase(db);
    return;
}

BitcoinExchange::BitcoinExchange()
{
    std::cout << GREY << "BitcoinExchange default constructor" << RESET << std::endl;
    return;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
    std::cout << GREY << "BitcoinExchange copy constructor" << RESET << std::endl;
    /*TODO*/;
    (void)other;
    return;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    std::cout << GREY << "BitcoinExchange copy assignment operator" << RESET << std::endl;
    if (this != &other)
    {
        /*TODO*/;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << GREY << "BitcoinExchange destructor" << RESET << std::endl;
    return;
}

/********************************************/
/********************************************/
/****** STREAM ******/

// std::ostream &operator<<(std::ostream &o, const BitcoinExchange &infile)
// {
//     o << "";
//     return o;
// }

/********************************************/
/********************************************/
/****** PRIVATE ******/
