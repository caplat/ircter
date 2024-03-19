#include <iostream>
#include <sys/socket.h> /* Tout ce qui est lie aux socket*/
#include <cstdlib>
#include <sys/types.h> /* Utilise certaines macros */
#include <netdb.h> /* gethostbyname*/
#include <errno.h>
#include <cstring> /*std::strerror*/
#include <unistd.h> /* */

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    
    int _error = errno;
    std::cout << PF_INET6 << std::endl;
    int _so = socket(PF_INET, SOCK_STREAM, 0);
    std::cout << "fd socket : " << _so << std::endl;

    addrinfo _addr;
    std::cout << "addrinfo.ai_family : " <<_addr.ai_family << std::endl;
    
    
    sockaddr _serv; 
    _serv.sa_family = PF_INET;
    std::cout << "SOCKADDR" << std::endl;
    std::cout << "_sockaddr.sa_family : " << _serv.sa_family << std::endl;
    
    hostent *_host;
    _host =  gethostbyname("k0r3p8.42mulhouse.fr");
    std::cout << "HOST" << std::endl;
    std::cout << "_host->h_addrtype : " << _host->h_addrtype << std::endl;
    std::cout << "_host->h_length : " <<_host->h_length << std::endl; 
    std::cout << "_PATH_HOSTS : " <<_PATH_HOSTS << std::endl;

    int _named = bind(_so, &_serv, sizeof(_so));
    std::cout << "Try to bind socket" << std::endl;
    if (_named == -1)
        std::cout << _error << " : " << std::strerror(errno) << std::endl;
    close(_so);
}