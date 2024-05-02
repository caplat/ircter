#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "User.hpp"


class Chan : public User
{
	private:
		std::map<size_t, User*> _users;
		static std::string _topic;
		static int _i;
		static int _t;
		static int _o;
		static int _l;

	public:	
		Chan(User &);
};


#endif