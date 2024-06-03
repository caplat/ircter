#include "Channel.hpp"

Chan::Chan(User& _op, std::string _n, std::string password) : _name(_n), _operator(&_op)
{
	_users.insert(std::make_pair(&_op, std::string("@")));
	std::cout << "password in chan is: " << password << std::endl;
	_mode = "t";
	if (password.empty())
	{
		_pswd = password;
		_mode.push_back('k');
	}
	_topic = "";
	_limuser = 0;
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

size_t Chan::get_limuser()
{
	return (_limuser);
}

std::map<User*, std::string> Chan::get_mapuser()
{
	return (_users);
}

std::vector<User*> Chan::get_banUser()
{
	return (_banUser);
}

void Chan::set_mode(std::string str)
{
	_mode = str;
}

void Chan::set_lk(char c, std::string str)
{
	if (c == 'k')
	{
	//	if (_mode.find('k') == std::string::npos)
			//_mode.push_back('k');
		_pswd = str;
	}
	else if (c == 'l')
	{
		//if (_mode.find('l') == std::string::npos)
			//_mode.push_back('l');
		_limuser = atoi(str.c_str());
	}
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
		std::cout << i->second << "\n";
		_str += i->second;
		_str += i->first->get_name();
		_str += " ";
	}
	std::cout << "built rpl_string : " << _str << std::endl;
	return (_str);
}

bool Chan::findbannedUser(User* user)
{
	for (size_t i = 0; i < _banUser.size(); i++)
	{
		if (user->get_name() == _banUser[i]->get_name())
		return (1);
	}
	return (0);
	
}
