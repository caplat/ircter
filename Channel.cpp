#include "Channel.hpp"

Chan::Chan(User &_operator) : User(_operator)
{
	_users.insert(std::make_pair(this->getpollfd().fd, &_operator));
}