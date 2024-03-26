#include "Pollfds.hpp"

Poll_fds::Poll_fds(int* fds, int size_fds, short int* events)
{
    _poll_fds = (pollfd*)calloc(size_fds, sizeof(pollfd));
    _size_fds = size_fds;
    for(int i = 0; i < size_fds; i++)
    {
        _poll_fds[i].fd = fds[i];
        _poll_fds[i].events = events[i];
    }
}

Poll_fds::~Poll_fds()
{
    clear_fds();
}

Poll_fds::Poll_fds(const Poll_fds & src)
{
   *this = src; 
}

Poll_fds & Poll_fds::operator=(const Poll_fds & src)
{
    _poll_fds = (pollfd*)calloc(src._size_fds, sizeof(pollfd));
    _size_fds = src._size_fds;
    for(int i = 0; i < src._size_fds; i++)
    {
        _poll_fds[i].fd = src._poll_fds[i].fd;
        _poll_fds[i].events = src._poll_fds[i].events;
    }
    return (*this);
}

void Poll_fds::clear_fds()
{
    memset(_poll_fds, 0, _size_fds);
    free(_poll_fds);
}

void Poll_fds::new_fds(int fd, short event)
{
    pollfd* tmp;

    tmp = (pollfd*)calloc(_size_fds + 1, sizeof(pollfd));
    for (int i = 0; i < _size_fds; i++)
    {
        tmp[i].fd = _poll_fds[i].fd;   
        tmp[i].events = _poll_fds[i].events;   
        tmp[i].revents = _poll_fds[i].revents;   
    }
    tmp[_size_fds].fd = fd; 
    tmp[_size_fds].events = event; 
    _size_fds += _size_fds;
    clear_fds();
    _poll_fds = tmp;
    std::cout << "fd[0] : " << tmp[0].fd << std::endl;
}

short int   Poll_fds::getevents(int fd)
{
    for(int i = 0; i < _size_fds; i++)
    {
        if (_poll_fds[i].fd == fd)
            return (_poll_fds[i].events);
    }
    return (-1);
}

short int   Poll_fds::getrevents(int fd)
{
    for(int i = 0; i < _size_fds; i++)
    {
        if (_poll_fds[i].fd == fd)
            return (_poll_fds[i].events);
    }
    return (-1);
}

int Poll_fds::getsize_fds()
{
    return (_size_fds);
}

int Poll_fds::getfd_fds(int fd)
{
    for (int i = 0; i < _size_fds; i++)
    {
        if (_poll_fds[i].fd == fd)
            return (fd);
    }
    return (0);
    
}

pollfd* Poll_fds::getpoll_fds()
{
    return(_poll_fds);
}

int Poll_fds::fdpollin_fds(int f)
{
    for (int i = 0; i < _size_fds; i++)
    {
        if (_poll_fds[i].revents != POLLIN)
            continue;
        else
        {
            _pullin.push_back(_poll_fds[i]);
            return(_poll_fds[i].fd);
        }
    }
    return (-1);
    
}

std::ostream& operator<<(std::ostream & f, Poll_fds & src)
{
   for (int i = 0; i < src.getsize_fds(); i++)
   {
        f << "fd[" << i << "] : " << src.getpoll_fds()[i].fd
        << "\t event : " << src.getpoll_fds()[i].events << "\t revents : "
        << src.getpoll_fds()[i].revents << std::endl;
   }
   return (f);
    
}