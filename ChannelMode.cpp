#include "Server.hpp"

std::string parseMode(char c, std::string newmode, Chan* channel)
{
	std::string _mode = channel->get_mode();
	std::string _rpl = "";
	for (size_t i = 0; i < newmode.size(); i++)
	{
		if(c == '+' &&  std::string("tklbio").find(newmode[i]) != std::string::npos)
		{	
			if (_mode.find_first_of(newmode[i]) == std::string::npos && newmode[i] != 'o')
				_mode.push_back(newmode[i]);
			_rpl.push_back(newmode[i]);	
		}
		else if (c == '-' && std::string("tklbio").find(newmode[i]) != std::string::npos)
		{
			if (_mode.size() < 2)
				_mode.clear();
			else if (_mode.find_first_of(newmode[i]) != std::string::npos)
				_mode.erase(_mode.find_first_of(newmode[i]), 1);
			_rpl.push_back(newmode[i]);	
		}
	}
	channel->set_mode(_mode);
	if (!_rpl.empty())
		_rpl.insert(_rpl.begin(), c);
	return(_rpl);
}

void parse_lk(std::vector<std::string> & _cmdparse, Chan *_here, char sign)
{
	size_t length_input = _cmdparse.size();
	size_t _indexofletter = 0;

	while (--length_input >= 3 && sign == '+')
	{
		_indexofletter = _cmdparse[2].find_first_of("lko", _indexofletter);
		_here->set_lk(_cmdparse[2][_indexofletter], _cmdparse[length_input]);
		_indexofletter++;
	}
	while (_cmdparse[2].find_first_of("lko", _indexofletter) != std::string::npos && sign == '+')
	{
		std::cout << "delete of: " << _cmdparse[2][_indexofletter] << std::endl;
		_cmdparse[2].erase(_indexofletter, 1);
		_here->set_lk(_cmdparse[2][_indexofletter], "");
		_indexofletter++;
	}
}

std::string rplLK(std::string str, Chan* _here)
{
	std::string _rpl = "";
	if (std::string("lko").find_first_of(str) == 0)
	{
		_rpl.push_back(' ');
		_rpl += NumberToString(_here->get_limuser());
		
	}
	if (std::string("lko").find_last_of(str) == 1)
	{
		_rpl.push_back(' ');
		_rpl += _here->get_password();
	}
	if (std::string("lko").find_last_of(str) == 1)
	{
		_rpl.push_back(' ');
		_rpl += _here->get_password();
	}
	return (_rpl);
}

void Server::modeChannel(User &user)
{
	char _sign = '+';
	std::string _rpl = "";
	size_t _index = 0;
	Chan* _here = already_channel(to_upper(_cmdparse[1]));
	(void)user;

	std::cout << _cmdparse[1] << &_here << std::endl;
	if (!(_here))
	{
		std::cout << "Unknown channel" << std::endl;
		throw( ERR_NOSUCHCHANNEL(this, user.get_name(), _cmdparse[1]));
	}
	if (_cmdparse.size() == 2)
	{
		std::cout << "No mode" << std::endl;
		throw(RPL_CHANNELMODEIS(this, user.get_name(), _here->get_name(), _here->get_mode(), rplLK(_here->get_mode(), _here)));
	}
	_index = _cmdparse[2].find_first_not_of("+-", _index);	
	while (_index != std::string::npos && _sign != '\0')
	{
		if (_cmdparse[2][_index - 1] == '+')	
			_sign = '+';
		else if (_cmdparse[2][_index - 1] == '-')	
			_sign = '-';
		else
			_sign = '\0';
		_cmdparse[2] = _cmdparse[2].substr(_index, _cmdparse[2].size() - _index);
		std::cout << "substr: " << _cmdparse[2] << std::endl;
		parse_lk(_cmdparse, _here, _sign);
		_rpl += parseMode(_sign, _cmdparse[2].substr(0, _cmdparse[2].size()), _here);
		std::cout << "new channel mode: " << _here->get_mode() << std::endl;
		_index = _cmdparse[2].find_first_not_of("+-", _index++);	
	}
	_rpl += rplLK(_cmdparse[2], _here);
	if (!_rpl.empty())
	{
		set_rpl(RPL_MODECHANNEL(user.get_name(), _here->get_name(), _rpl));
	}
}