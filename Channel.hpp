#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "User.hpp"
#include <map>
#include <vector>

class User;

class Chan
{
	private:
		std::map<User*, std::string> _users;
		typedef	std::map<User*, std::string>::iterator _it;
		std::string _name;
		std::string _topic;
		int _i;
		int _t;
		int _o;
		int _l;
		User* _operator;

	public:	
		Chan(User&, std::string);
		
		std::string get_name();
		User* get_operator();
		void add_user(User*);
		std::string string_for_rpl();
};


#endif