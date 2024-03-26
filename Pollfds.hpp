#ifndef POLL_FDS
#define POLL_FDS
#include <poll.h>
#include <unistd.h> /* */
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

typedef struct _p
{
    int fd;
    short int events;
    short int revents;
} pollfd;

class Poll_fds
{
    pollfd * _poll_fds;
    int _size_fds;
    std::vector<pullfd> _pullin;
    public:
        Poll_fds(int*, int, short int*);
        ~Poll_fds();
        Poll_fds(const Poll_fds &);
        Poll_fds & operator=(const Poll_fds &);
        void new_fds(int, short);
        short int getevents(int);
        short int getrevents(int);
        int fdpollin_fds(int);
        int getsize_fds();
        int getfd_fds(int);
        pollfd* getpoll_fds();
        void clear_fds();
};


std::ostream& operator<<(std::ostream &, Poll_fds &);

#endif