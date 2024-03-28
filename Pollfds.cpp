#include "Pollfds.hpp"

Poll_fds::Poll_fds(int* fds, int size_fds, short int* events)
{
    pollfd _a;
    for (int i = 0; i < size_fds; i++)
    { 
        _a.fd = fds[i];
        _a.events = events[i];
        _fds.push_back(_a);
    }
    
}

Poll_fds::~Poll_fds()
{
}

Poll_fds::Poll_fds(const Poll_fds & src)
{
   *this = src; 
}

Poll_fds & Poll_fds::operator=(const Poll_fds & src)
{
    _fds = src._fds;
    _pollin = src._pollin;
    return (*this);
}

void Poll_fds::new_fds(int fd, short event)
{
    pollfd _a;

    _a.fd = fd;
    _a.events = event;
    _fds.push_back(_a);
}

short int   Poll_fds::getevents(int fd)
{
    for(size_t i = 0; i < _fds.size(); i++)
    {
        if (_fds[i].fd == fd)
            return (_fds[i].events);
    }
    return (-1);
}

short int   Poll_fds::getrevents(int fd)
{
    for(size_t i = 0; i < _fds.size(); i++)
    {
        if (_fds[i].fd == fd)
            return (_fds[i].revents);
    }
    return (-1);
}

size_t Poll_fds::getsize_fds()
{
    return (_fds.size());
}

int Poll_fds::getfd_fds(int fd)
{
    for (size_t i = 0; i < _fds.size(); i++)
    {
        if (_fds[i].fd == fd)
            return (fd);
    }
    return (0);
    
}

std::vector<pollfd> Poll_fds::getpoll_fds()
{
    return(_fds);
}

int Poll_fds::fdpollin_fds()
{
    for (size_t i = 0; i < _fds.size(); i++)
    {
        if (_fds[i].revents != POLLIN)
            continue;
        else
        {
            _pollin.push_back((*_fds)[i]);
            _fds[i].revents = 0;
            return(_fds[i].fd);
        }
    }
    return (-1);
    
}

std::ostream& operator<<(std::ostream & f, Poll_fds & src)
{
    for (size_t i = 0; i < src.getsize_fds(); i++)
    {
        f << "vector[" << i << "] : " << src.getpoll_fds()[i].fd << std::endl;
    }
    
   return (f);
    
}