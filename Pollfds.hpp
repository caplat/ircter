#ifndef POLL_FDS
#define POLL_FDS
#include <poll.h>
#include <unistd.h> /* */
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

class Poll_fds
{
    std::vector<pollfd> _pollin;
    std::vector<pollfd> *_fds;
    public:
        Poll_fds(int*, int, short int*);
        ~Poll_fds();
        Poll_fds(const Poll_fds &);
        Poll_fds & operator=(const Poll_fds &);
        void new_fds(int, short);
        short int getevents(int);
        short int getrevents(int);
        int fdpollin_fds();
        size_t getsize_fds();
        int getfd_fds(int);
        std::vector<pollfd> getpoll_fds();
};


std::ostream& operator<<(std::ostream &, Poll_fds &);

#endif