#include "User.hpp"

void Server::privateMsg(User &sender){

    std::string msg = _cmdparse[2];
    if(findReceiver() == 0)
    {
        // send_message(sender.getsock(), ERR_NOSUCHNICK(_cmdparse[1], this));
        // throw std::runtime_error(ERR_NOSUCHNICK(_cmdparse[1], this));
        set_rpl(ERR_NOSUCHNICK(_cmdparse[1], this));
    }
    if(findReceiver() == 1)
    {
        User* receiver;
        receiver = findUserbyname(_cmdparse[1]);
        int fd = receiver->getsock();
        _sendfd.clear();
        _sendfd.push_back(fd);
        // set_rpl(":" + sender.get_name() + " PRIVMSG " + receiver->get_name()+ " :" + msg + "\r\n");
        set_rpl(PRIV_MSG_TO_USER(sender, receiver, msg));
    }
    if(findReceiver() == 2)
    {
        Chan* channel;
        std::string channel_name = _cmdparse[1];
        channel = findChannelName(channel_name);
        // if(channel == nullptr)
        //     throw std::runtime_error("Channel not found");
        // const std::map<User*, std::string> &users = channel->get_users();
        // for (std::map<User*, std::string>::const_iterator it = users.begin(); it != users.end(); ++it){

        //     User* user = it->first;
        //     int fd = user->getsock();
        //     // send_message(fd, sender.get_name() + " " + "PRIVMSG " + channel->get_name() + " " + msg);
        // }
        _sendfd.clear();
        channel->send_msg_to(_sendfd, sender.getpollfd().fd);
        // set_rpl(":" + sender.get_name() + " PRIVMSG " + channel->get_name() + " :" + msg + "\r\n");
        set_rpl(PRIV_MSG_TO_CHANNEL(sender, channel, msg));
    }
}

int Server::findReceiver(){

    if(_cmdparse.size() >= 2)
    {
        for(std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++){

            if(_cmdparse[1] == it->second.get_name())
                return 1;
        }
        for(std::vector<Chan*>::iterator it = _chan.begin(); it != _chan.end(); it++){    
            if(_cmdparse[1] == (*it)->get_name())
                return 2;
        }
    }
    return 0;
}

Chan* Server::findChannelName(const std::string& channel_name) {
    for (size_t i = 0; i < _chan.size(); ++i) {
        if (_chan[i]->get_name() == channel_name) {
            return _chan[i];
        }
    }
    return nullptr;
}
