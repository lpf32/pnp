#ifndef PNP_SOCKET_H
#define PNP_SOCKET_H

#include "Common.h"
#include <utility>

class InetAddress;

class Socket : noncopyable
{
public:
    explicit Socket(int sockfd);
    ~Socket();

    Socket(Socket&& rhs)
        : Socket(rhs.sockfd_)
    {
        rhs.sockfd_ = -1;
    }

    Socket& operator=(Socket&& rhs)
    {
        swap(rhs);
        return *this;
    }

    void swap(Socket& rhs)
    {
        std::swap(sockfd_, rhs.sockfd_);
    }

    int fd() { return sockfd_; }

    // Socket API
    void bindOrDie(const InetAddress& addr);
    void listenOrDie();

    int connect(const InetAddress& addr);
    void shutdownWrite();

    void setReuseAddr(bool on);
    void setTcpNoDelay(bool on);

    InetAddress getLocalAddr() const;
    InetAddress getPerrAddr() const;

    int read(void *buf, int len);
    int write(const void* buf, int len);

    // factory methods
    static Socket createTcp();
    static Socket createUDP();


private:
    int sockfd_;
};
#endif //PNP_SOCKET_H
