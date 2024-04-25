#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "User.hpp"


class Chan : public User
{
	private:
	std::map<char, int> _modes;
	std::string _topic;

	public:
	

};


#endif