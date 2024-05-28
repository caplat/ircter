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

void Server::modeChannel(User &user)
{
	char _sign = '+';
	size_t i = 2;
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
	if (_cmdparse.size() <= 2)
	{
		std::cout << "No mode" << std::endl;
		return ;
		//return RPL_channnomodeis
	}
	while (i < _cmdparse.size())
	{
		std::cout << "parameter: " << _cmdparse[i] << std::endl;
		_index = _cmdparse[i].find_first_not_of("+-", _index);
		if (_index == std::string::npos)
			return ;
		else if (_cmdparse[i][_index - 1] == '+')	
			_sign = '+';
		else if (_cmdparse[i][_index - 1] == '-')	
			_sign = '-';
		_cmdparse[i] = _cmdparse[i].substr(_index, _cmdparse[i].size() - _index);
		std::cout << "substr: " << _cmdparse[i] << std::endl;
		_index = _cmdparse[i].find_first_not_of("tklbi", _index);
		std::cout << _index << std::endl;
		if (_index != std::string::npos && _sign != '\0')
		{
			std::cout << "Channel Mode unknow: " << _cmdparse[i][_index] << std::endl;
			parseMode(_sign, _cmdparse[i].substr(0, _index), _here);
			std::cout << "new channel mode: " << _here->get_mode() << std::endl;
			_index++;
			//return tout les modes connus avant le mode inconnu
			//return ERR_UMODEUNKNOW
		}
		else
		{
			//return les modes 1 par 1
			i++;
		}
		
	}
}