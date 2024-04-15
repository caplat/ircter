#include "utilsTosend.hpp"

std::string getstr_time()
{
    std::time_t currentTime = std::time(NULL);
    std::tm* localTime = std::localtime(&currentTime);
    std::string str;
    std::stringstream ss;

    const char* daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    str += daysOfWeek[localTime->tm_mday % 7];
    str += " ";
    str += months[localTime->tm_mon];
    str += " ";
    ss << localTime->tm_mday;
    str += ss.str();
    ss.str("");
    str += " ";
    ss << localTime->tm_year + 1900;
    str += ss.str();
    return (str);
}
