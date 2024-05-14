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

	public:
		Server();
		~Server();
		void set_host();
		addrinfo& getaddrinfo_serv();

		int getsock_serv();
		int getRevents();
		std::string gethostname_srv();
		std::map<int, User>& getUsers();
		User* findUser(int);
		User* findUserbyname(std::string);
		void set_channel(Chan*);
		Chan* already_channel(std::string);

		void makepollfd_fds();
		void make_sockserv();

		void run_serv();
		void readfds_serv(int);
		void sendfds_serv(int);
		void accept_conection_serv();
		void set_rpl(std::string);
		void clear_rpl();
};
std::ostream& operator<<(std::ostream&, Server&); 

#endif