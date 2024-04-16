#include <iostream>
#include <netinet/in.h> /* sockaddr_in*/
#include <sys/socket.h> /* Tout ce qui est lie aux socket*/
#include <vector>
#include "Server.hpp"

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;
	
	try
	{
		Server _s; 
		_s.run_serv();
	}
	catch(int e)
	{
		std::cerr << e << '\n';
	}


}