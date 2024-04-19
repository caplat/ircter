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

class Server;

class User
{
    private:
        std::string _name, _pass, _userMode, _username, _realname;
        int _so;
        std::list<std::string> _chan;
        std::string _str;
        pollfd _fd;
        int _regis;
        Server * _server;
    public:
		typedef void (*f)();
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

        void setstr(char*);
		void set_name(std::string);
		void set_pass(std::string);

        void registration();
        void setup_nick();
		void setup_user();
		void test();
		void trim_cmds();
		void cmds();
		int find_cmds();

};



#endif