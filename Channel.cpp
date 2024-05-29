#include "Channel.hpp"

Chan::Chan(User& _op, std::string _n, std::string password) : _name(_n), _operator(&_op)
{
	_users.insert(std::make_pair(&_op, std::string("@")));
	_pswd = password;
	_topic = "";
	_limuser = 0;
	_mode = "itklb";
	std::cout << _op.get_name() << std::endl;
	std::cout << _users.begin()->first->get_name() << std::endl;
}

std::string Chan::get_name()
{
	return (_name);
}
User* Chan::get_operator()
{
	return (_operator);
}

std::string Chan::get_password()
{
	return (_pswd);
}

std::string Chan::get_mode()
{
	return (_mode);
}

void Chan::set_mode(std::string str)
{
	_mode = str;
}

void Chan::set_lk(char c, std::string str)
{
	(void)c;
	(void)str;	
}

void Chan::add_mode(char c)
{
	_mode.push_back(c);
}

void Chan::add_user(User* user)
{
	_users.insert(std::make_pair(user, std::string("")));
}

std::string Chan::string_for_rpl()
{
	std::string _str = "";
	if (_users.size() < 2)
	{
		_str += _users.begin()->second;
		_str += _users.begin()->first->get_name();
		return (_str);
	}
	for (_it i = _users.begin(); i != _users.end(); i++)
	{
		std::cout << i->second << "\t";
		_str += _users.begin()->second;
		_str += _users.begin()->first->get_name();
		_str += " ";
	}
	std::cout << "built rpl_string : " << _str << std::endl;
	return (_str);
}
