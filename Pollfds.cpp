#include "Pollfds.hpp"

Poll_fds::Poll_fds(int* fds, int size_fds, short int* events) : _poll(0), _size_poll(0)
{
    pollfd _a;
    for (int i = 0; i < size_fds; i++)
    { 
        _a.fd = fds[i];
        _a.events = events[i];
        _fds.push_back(_a);
    }
    
}

Poll_fds::Poll_fds() : _poll(0), _size_poll(0)
{}

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

std::vector<pollfd> Poll_fds::getvector_fds()
{
    return(_fds);
}

int Poll_fds::fdpollin_fds()
{
    for (size_t i = 0; i < _size_poll; i++)
    {
        if (_poll[i].revents == POLLIN)
        {
            _pollin.push_back(_poll[i]);
            return(_poll[i].fd);
        }
    }
    return (-1);
    
}

pollfd* Poll_fds::getpollfd_fds()
{
    if (_fds.size() != _size_poll && _size_poll > 0)
        delete _poll;
    else if( _size_poll > 0)
        return _poll;
    _poll = new pollfd[_fds.size()];
    for (size_t i = 0; i < _fds.size(); i++)
    {
        _poll[i] = _fds[i];
    }
    _size_poll = _fds.size();
    return (_poll);
    
}

std::ostream& operator<<(std::ostream & f, Poll_fds & src)
{
    for (size_t i = 0; i < src.getsize_fds(); i++)
    {
        f << "vector[" << i << "] fd : " << src.getvector_fds()[i].fd
        << "\tevent : " << src.getvector_fds()[i].events
        << "\trevent : " << src.getvector_fds()[i].revents << std::endl;
    }
    
   return (f);
    
}