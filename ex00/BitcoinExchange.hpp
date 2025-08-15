#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <exception>
#include <map>

#ifndef COLOR
#define COLOR
#define GREY "\033[0;30m"
#define RESET "\033[0m"
#endif

class BitcoinExchange
{
public:
    // controller (main)
    // model - enforces rules & performs logic
    // view cout/cerr also in main i guess
    BitcoinExchange(const std::string &db);
    ~BitcoinExchange();

    void updateDataBase(const std::string &db);
    double executeLine(const std::string &date, double amountBTC);

    class InputError : public std::exception
    {
    public:
        InputError(const std::string &msg) : _msg(msg) {}
        virtual ~InputError() throw() {}
        virtual const char *what() const throw()
        {
            return _msg.c_str();
        }

    private:
        std::string _msg;
    };

private:
    // bool extractDate(const std::string &s, int &y, int &m, int &d);
    bool extractDate(const std::string &s);
    std::map<std::string, double> data;
    BitcoinExchange();
    BitcoinExchange(BitcoinExchange const &other);
    BitcoinExchange &operator=(BitcoinExchange const &other);
};

std::ostream &operator<<(std::ostream &o, BitcoinExchange const &infile);

#endif
