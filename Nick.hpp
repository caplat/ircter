#ifndef NICK_HPP
#define NICK_HPP

#include <cstring>
#include <iostream>
void setup_nick(std::string str)
{
    size_t _index = str.find(" ");
    while (++_index < str.size())
    {
        if(!isalpha(str[_index]))
        {
            std::cout << "Error nickname\n";
            return ;
        }
    }
       
}

#endif