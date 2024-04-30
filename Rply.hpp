#ifndef RPLY_HPP
#define RPLY_HPP
#include "Server.hpp"
#include "utilsTosend.hpp"

class Server;

#define MAXCHANLEN 20
#define MAXNICKLEN 20
#define MAXUSERLEN 20
#define MAXTOPICLEN 510


#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define RESET_TEXT "\033[0m"

#define BEGIN_RPL(server) (":" + server->gethostname_srv())

#define RPL_WELCOME(server, nick) (BEGIN_RPL(server) + " 001 " + nick + " :Welcome to the IRC Network, " + nick + "\r\n")
#define RPL_YOURHOST(server, nick) (BEGIN_RPL(server) + " 002 " + nick + " :Your host is Flower, running version 0.1\r\n")
#define RPL_CREATED(server, nick) (BEGIN_RPL(server) + " 003 " + nick + " :This server was created " + getstr_time() + "\r\n")
#define RPL_MYINFO(server, nick)  (BEGIN_RPL(server) + " 004 " + nick + " :Flower 0.1  iOr CHANMODE=itkol\r\n")
#define RPL_ISUPPORT(server, nick)  (BEGIN_RPL(server) + " 005 " + nick + " ARGMAX=NICK:1:are suported by this server\r\n")
#define RPL_MOTD(server, nick)  (BEGIN_RPL(server) + " 005 " + nick + " :- Flower message of the day -\n" + \
"  _____   _ \n\
 |  ___| | |   ___   __      __   ___   _ __ \n\
 | |_    | |  / _ \\  \\ \\ /\\ / /  / _ \\ | '__|\n\
 |  _|   | | | (_) |  \\ V  V /  |  __/ | |   \n\
 |_|     |_|  \\___/    \\_/\\_/    \\___| |_| \r\n")

#define RPL_ENDOFMOTD(server, nick) (BEGIN_RPL(server) + " 376 " + nick + " :END of /MOTD command.\r\n")

#define RPL_UMODEIS(server, nick, mode) (BEGIN_RPL(server) + " 221 " + nick + " :"  + nick + " " + mode + "\r\n") 
#define RPL_MODE(server, nick, signe, mode) (BEGIN_RPL(server) + " MODE " + nick + " :" + signe + mode + "\r\n") 
#define ERR_USERSDONTMATCH(server, nick) (BEGIN_RPL(server) + " 502 " + nick + " :Can't changemode for other users\r\n") 

#define RPL_PING(server, nick, str) (BEGIN_RPL(server) + " PONG " + nick + " :" + str + "\r\n")
#define RPL_PONG(server, nick, str) (BEGIN_RPL(server) + " PING " + nick + " :" + str + "\r\n")


#define RPL_NICK(server, oldnick, nick) (":" + oldnick + "!d@lcoalhost" +  " NICK " + nick  + "\r\n")
#define ERR_NONICKNAMEGIVEN(server, nick) (BEGIN_RPL(server) + " 431 " + nick + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(server, nick) (BEGIN_RPL(server) + " 432 " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(server, nick) (BEGIN_RPL(server) + " 433 " + nick + " :Nickname is already in use\r\n")

#endif