#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <poll.h>
#include <list>
#include <cstring>
#include <map>
#include "Server.hpp"
#include "Rply.hpp"
#include <algorithm>
#include <cstdlib>
#include "Channel.hpp"
#include <vector>
#include "utilsTosend.hpp"

class Server;
class Chan;

class User
{
    private:
        std::string _name, _pass, _userMode, _username, _realname;
        int _so;
     	std::vector<Chan*> _chan;
        std::string _str;
		std::string _cmd;
        pollfd _fd;
        int _regis;
        Server * _server;

    public:
        User(int, Server &);
        ~User();
        int getsock();
        std::string& getstr();
        int getregis();
        Server* getServer();
        pollfd& getpollfd();
		std::string get_name();
		std::string get_pass();
		std::string get_Usermode();
		Chan* get_channel(std::string);

        void setstr(char*);
		void set_name(std::string);
		void set_pass(std::string);

        void registration();
        void setup_nick();
		void setup_user();
		void set_mode();
		void join();
		void test();
		void trim_cmds();
		void cmds_register();
		void cmds();
		int find_cmds();

};



#endif