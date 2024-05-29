#include "Server.hpp"

void parseMode(char c, std::string newmode, Chan* channel)
{
	std::string _mode = channel->get_mode();
	for (size_t i = 0; i < newmode.size(); i++)
	{
		if(c == '+' && _mode.find_first_of(newmode[i]) == std::string::npos)
		{
			_mode.push_back(newmode[i]);
		}
		else if (c == '-' && _mode.find_first_of(newmode[i]) != std::string::npos)
		{
			if (_mode.size() < 2)
				_mode.clear();
			else
				_mode.erase(_mode.find_first_of(newmode[i]), 1);
		}
	}
	channel->set_mode(_mode);
}

void parse_lk(std::vector<std::string> & _cmdparse, Chan *_here, char sign)
{
	if (sign == '+' && _cmdparse[2].find('l') != std::string::npos && _cmdparse[2].find('k') != std::string::npos && _cmdparse.size() == 5)
	{
		_here->set_lk(_cmdparse[2].find_first_of("lk", 0), _cmdparse[3]);
		_here->set_lk(_cmdparse[2].find_last_of("lk", _cmdparse[2].size()), _cmdparse[4]);
	}
	else if (sign == '+' && _cmdparse[2].find_first_of("lk") != std::string::npos && _cmdparse.size() >= 4)
	{
		_here->set_lk(_cmdparse[2].find_first_of("lk", 0), _cmdparse[3]);
		if (_cmdparse[2].find_last_of("lk", _cmdparse[2].size()) != std::string::npos && _cmdparse[2].find_last_of("lk", _cmdparse[2].size()) != _cmdparse[2].find_first_of("lk"))
			_cmdparse[2].erase(_cmdparse[2].find_last_of("lk", _cmdparse.size()), 1);
	}
	else if (sign == '+' && _cmdparse[2].find_first_of("lk") != std::string::npos)
	{
		_cmdparse[2].erase(_cmdparse[2].find_first_of("lk"), 1);
		if (_cmdparse[2].find_first_of("lk") != std::string::npos)
			_cmdparse[2].erase(_cmdparse[2].find_first_of("lk"), 1);
	}
}

void Server::modeChannel(User &user)
{
	char _sign = '+';
	size_t _index = 0;
	Chan* _here = already_channel(to_upper(_cmdparse[1]));
	(void)user;

	std::cout << _cmdparse[1] << &_here << std::endl;
	if (!(_here))
	{
		std::cout << "Unknown channel" << std::endl;
		throw( ERR_NOSUCHCHANNEL(this, user.get_name(), _cmdparse[1]));
		return ;
	}
	if (_cmdparse.size() == 2)
	{
		std::cout << "No mode" << std::endl;
		return ;
		//return RPL_channnomodeis
	}
	while (_index != _cmdparse[2].size())
	{
		std::cout << "parameter: " << _cmdparse[2] << std::endl;
		_index = _cmdparse[2].find_first_not_of("+-", _index);
		if (_index == std::string::npos)
			return ;
		else if (_cmdparse[2][_index - 1] == '+')	
			_sign = '+';
		else if (_cmdparse[2][_index - 1] == '-')	
			_sign = '-';
		_cmdparse[2] = _cmdparse[2].substr(_index, _cmdparse[2].size() - _index);
		std::cout << "substr: " << _cmdparse[2] << std::endl;
		_index = _cmdparse[2].find_first_not_of("tklbi", _index);
		std::cout << _index << std::endl;
		parse_lk(_cmdparse, _here, _sign);
		if (_index != std::string::npos && _sign != '\0')
		{
			std::cout << "Channel Mode unknow: " << _cmdparse[2][_index] << std::endl;
			parseMode(_sign, _cmdparse[2].substr(0, _index), _here);
			std::cout << "new channel mode: " << _here->get_mode() << std::endl;
			_index++;
			//return tout les modes connus avant le mode inconnu
			//return ERR_UMODEUNKNOW
		}
		else
		{
			std::cout << "All channel Mode know: " << _cmdparse[2][_index] << std::endl;
			parseMode(_sign, _cmdparse[2].substr(0, _cmdparse[2].size()), _here);
			std::cout << "new channel mode: " << _here->get_mode() << std::endl;
			//return les modes 1 par 1
			_index = _cmdparse[2].size();
		}
		
	}
}