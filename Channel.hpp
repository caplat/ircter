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
		std::string _pswd;
		size_t _limuser;
		std::string _mode;
		User* _operator;

	public:	
		Chan(User&, std::string, std::string);
		
		//getteur
		std::string get_name();
		User* get_operator();
		std::string get_password();
		std::string get_mode();

		//setteur
		void set_mode(std::string);
		void add_mode(char);

		void add_user(User*);
		std::string string_for_rpl();
};


#endif