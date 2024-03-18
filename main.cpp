#include <iostream>
#include <sys/socket.h>
#include <cstdlib>
#include <sys/types.h>

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    // int _error = errno;
    std::cout << PF_INET6 << std::endl;
    int _so = socket(PF_INET6, SOCK_STREAM, 0);
    std::cout << _so << std::endl;
    sockaddr _serv; 

    std::cout << &_serv.sa_data << std::endl;

}