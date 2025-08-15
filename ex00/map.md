## FEATURES PLAN

1. parse the csv into map
2. process each line of the provided file
	1. make sure the date is legitimate
	2. make sure all the input exists (date | pos int/float)
	3. find the correcponding entry in map, peform math and output a line

## QUESTIONS

1. how can i find an element in a map that is smaller than the element i am looking for if the emelement i am looking for does not exist? Do i need to manually iterate through the map container and compare each value?












## REQUIREMENTS

1. Must take a file as argument
2. each line in file should be formatted like "date | value"
3. Date will be in Year-Month-Day format: 2000-06-06
4. value will be a positive int of float between 0 and 1000

### Example file:

input.txt  

date | value  
2011-01-03 | 3  
2011-01-03 | 2  
2011-01-03 | 1  
2011-01-03 | 1.2  
2011-01-09 | 1  
2012-01-11 | -1  
2001-42-42  
2012-01-11 | 1  
2012-01-11 | 2147483648  

5. Program will display on standard output the result of exchange rate * the number in the file

### Example output:

$> ./btc. 
Error: could not open file.  
$> ./btc input.txt  
2011-01-03 => 3 = 0.9  
2011-01-03 => 2 = 0.6  
2011-01-03 => 1 = 0.3  
2011-01-03 => 1.2 = 0.36  
2011-01-09 => 1 = 0.32  
Error: not a positive number.  
Error: bad input => 2001-42-42  
2012-01-11 => 1 = 7.1  
Error: too large a number.  

6. If date doesnt exist, use next lowest date


#include <iostream>
#include <sstream>
#include <ctime>

// function expects the string in format dd/mm/yyyy:
bool extractDate(const std::string& s, int& d, int& m, int& y){
    std::istringstream is(s);
    char delimiter;
    if (is >> d >> delimiter >> m >> delimiter >> y) {
        struct tm t = {0};
        t.tm_mday = d;
        t.tm_mon = m - 1;
        t.tm_year = y - 1900;
        t.tm_isdst = -1;

        // normalize:
        time_t when = mktime(&t);
        const struct tm *norm = localtime(&when);
        // the actual date would be:
        // m = norm->tm_mon + 1;
        // d = norm->tm_mday;
        // y = norm->tm_year;
        // e.g. 29/02/2013 would become 01/03/2013

        // validate (is the normalized date still the same?):
        return (norm->tm_mday == d    &&
                norm->tm_mon  == m - 1 &&
                norm->tm_year == y - 1900);
    }
    return false;
}