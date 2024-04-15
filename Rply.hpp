#ifndef RPLY_HPP
#define RPLY_HPP
#include "Server.hpp"
#include "utilsTosend.hpp"

class Server;

#define RPL_001(server, nick) (server->gethostname_srv() + " 001 :Welcome to the IRC Network, " + nick + "\r\n")
#define RPL_002(server) (server->gethostname_srv() + " 002 :Your host is Flower, running version 0.1\r\n")
#define RPL_003(server) (server->gethostname_srv() + " 003 :This server was created " + getstr_time() + "\r\n")
#define RPL_004(server)  (server->gethostname_srv() + " 004 Flower 0.1  ioOwr CHANMODE=itkol\
  <available channel modes> [<channel modes with a parameter>]\r\n" + \
"  _____   _ \n\
 |  ___| | |   ___   __      __   ___   _ __ \n\
 | |_    | |  / _ \\  \\ \\ /\\ / /  / _ \\ | '__|\n\
 |  _|   | | | (_) |  \\ V  V /  |  __/ | |   \n\
 |_|     |_|  \\___/    \\_/\\_/    \\___| |_| \r\n")
#endif