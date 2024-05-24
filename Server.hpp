#ifndef SERVER_HPP
#define SERVER_HPP
#include "User.hpp"
#include <iostream>
#include <vector>
#include <sys/types.h> /* Utilise certaines macros */
#include <unistd.h> /* */
#include <errno.h>
#include <netdb.h> /* gethostbyname*/
#include <utility>
#define _BUFF_SIZE 20

class User;
class Chan;

typedef  std::map<int, User>::iterator _ituser;
class Server
{
	private:
		addrinfo *_host;
		char _hostname[256];
		int _sock_serv;
		std::map<int, User> _users;
		std::vector<Chan*> _chan;
		pollfd* _poll;
		size_t _size_poll;
		std::vector<std::string> _rpl;
		std::string _bufferread;
		std::string _cmd;
		std::vector<std::string> _cmdparse;

	public:
		//constructor
		Server();
		~Server();

		//get something
		addrinfo& getaddrinfo_serv();
		int getsock_serv();
		int getRevents();
		std::string gethostname_srv();
		std::map<int, User>& getUsers();

		//find somthings
		User* findUser(int);
		User* findUserbyname(std::string);

		//Check something
		Chan* already_channel(std::string);

		//make/set/run/build something
		void set_channel(Chan*);
		void set_host();
		void makepollfd_fds();
		void make_sockserv();

		//Read/Write/Connection socket
		void run_serv();
		void readfds_serv(int);
		void sendfds_serv(int);
		void accept_conection_serv();
		void set_rpl(std::string);
		void clear_rpl();

		//run orders
		int find_cmds();
		void cmds_register(User &);
		void orders(User &);
		void trim_cmds();
		void parse_order();
		void run_order(User &);

		//orders
		void nick(User &);
		void user(User &);
		void modeUser(User &);
		void join(User &);

};
std::ostream& operator<<(std::ostream&, Server&); 

#endif