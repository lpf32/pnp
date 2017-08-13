#include "TcpStream.h"
#include "InetAddress.h"

#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

namespace
{
    class IgnoreSigPipe
    {
    public:
        IgnoreSigPipe()
        {
            ::signal(SIGPIPE, SIG_IGN);
        }
    } initObj;

    bool isSelfConnection(const Socket& sock)
    {
        return sock.getLocalAddr() == sock.getPerrAddr();
    }
}

TcpStream::TcpStream(Socket&& sock)
    : sock_(std::move(sock))
{

}

int TcpStream::receiveAll(void *buf, int len)
{
    return ::recv(sock_.fd(), buf, len, MSG_WAITALL);
}

int TcpStream::receiveSome(void *buf, int len)
{
    return sock_.read(buf, len);
}

int TcpStream::sendAll(const char *buf, int len)
{
    int written = 0;
    while (written < len)
    {
        int nw = sock_.write(buf, len-written);

        if (nw > 0)
        {
            written += nw;
        }
        else if (nw == 0)
        {
            break;
        }
        else if (errno != EINTR)
        {
            break;
        }
    }

    return written;
}

int TcpStream::sendSome(const void *buf, int len)
{
    return sock_.write(buf, len);
}

void TcpStream::setTcpNoDelay(bool on)
{
    sock_.setTcpNoDelay(on);
}

void TcpStream::shutdownWrite()
{
    sock_.shutdownWrite();
}

TcpStreamPtr TcpStream::connect(const InetAddress &serverAddr)
{
    return connectInternal(serverAddr, nullptr);
}

TcpStreamPtr TcpStream::connect(const InetAddress &serverAddr, const InetAddress &localAddr)
{
    return connectInternal(serverAddr, &localAddr);
}

TcpStreamPtr TcpStream::connectInternal(const InetAddress &serverAddr, const InetAddress *localaddr)
{
    TcpStreamPtr stream;
    Socket sock(Socket::createTcp());
    if (localaddr)
    {
        sock.bindOrDie(*localaddr);
    }
    if (sock.connect(serverAddr) == 0 && !isSelfConnection(sock))
    {
        stream.reset(new TcpStream(std::move(sock)));
    }

    return stream;
}
