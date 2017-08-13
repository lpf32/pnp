#include "Acceptor.h"

#include "TcpStream.h"

#include <stdio.h>
#include <sys/socket.h>
#include <cstdlib>

Acceptor::Acceptor(const InetAddress &listenAddr)
    : listenSock_(Socket::createTcp())
{
    listenSock_.setReuseAddr(true);
    listenSock_.bindOrDie(listenAddr);
    listenSock_.listenOrDie();
}

TcpStreamPtr Acceptor::accept()
{
    int sockfd = ::accept(listenSock_.fd(), NULL, NULL);
    if (sockfd >= 0)
    {
        return TcpStreamPtr(new TcpStream(Socket(sockfd)));
    }
    else
    {
        perror("Acceptor::accept");
        return TcpStreamPtr();
    }
}

Socket Acceptor::acceptSocketOrDir()
{
    int sockfd = ::accept(listenSock_.fd(), NULL, NULL);
    if (sockfd >= 0)
    {
        return Socket(sockfd);
    }
    else
    {
        perror("Acceptor::accept");
        abort();
    }
}