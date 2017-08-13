#ifndef PNP_ACCEPTOR_H
#define PNP_ACCEPTOR_H

#include "Common.h"
#include "Socket.h"

#include <memory>

class InetAddress;

class TcpStream;
typedef std::unique_ptr<TcpStream> TcpStreamPtr;

class Acceptor : noncopyable
{
public:
    explicit Acceptor(const InetAddress& listenAddress);

    ~Acceptor() = default;
    Acceptor(Acceptor&&) = default;
    Acceptor& operator=(Acceptor&&) = default;

    TcpStreamPtr accept();
    Socket acceptSocketOrDir();

private:
    Socket listenSock_;
};

#endif //PNP_ACCEPTOR_H
