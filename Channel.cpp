#include "Channel.hpp"

Chan::Chan(User& _op, std::string _n, std::string password) : _name(_n), _operator(&_op)
{
	_users.insert(std::make_pair(&_op, std::string("@")));
	_pswd = password;
	_topic = "";
	_i = 0;
	_t = 0;
	_o = 0;
	_l = 0;
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

void Chan::add_user(User* user)
{
	_users.insert(std::make_pair(user, std::string("")));
}

std::string Chan::string_for_rpl()
{
	std::string _str = "";
	std::cout << "HEEEEERRRRRREEEE" << std::endl;
	std::cout << _users.size() << std::endl;
	std::cout << _users.begin()->second << "\t";
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
