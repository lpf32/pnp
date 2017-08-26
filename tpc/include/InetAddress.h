#ifndef PNP_INETADDRESS_H
#define PNP_INETADDRESS_H

#include "Common.h"

#include <string>
#include <vector>
#include <netinet/in.h>

class InetAddress : copyable
{
public:
    InetAddress(StringArg ip, uint16_t port);
    explicit InetAddress(StringArg ipPort); // "1.2.3.4:5667"
    explicit InetAddress(uint16_t port, bool loopbackOnly = false);

    explicit InetAddress(const struct sockaddr_in& saddr)
        : saddr_(saddr)
    { }

    std::string toIp() const;
    std::string toIpPort() const;

    const struct sockaddr_in& getSockAddrInet() const { return saddr_; }
    void setSockAddrInet(const struct sockaddr_in& saddr) { saddr_ =  saddr; }

    void setPort(uint16_t port) { saddr_.sin_port = htons(port); }

    uint32_t ipNetEndian() const { return saddr_.sin_addr.s_addr; }
    uint16_t portNetEndian() const { return saddr_.sin_port; }

    uint32_t ipHostEndian() const { return ntohl(saddr_.sin_addr.s_addr); }
    uint16_t portHostEndian() const { return ntohs(saddr_.sin_port); }

    static bool resolve(StringArg hostname, InetAddress*);
    static std::vector<InetAddress> resolveAll(StringArg hostname, uint16_t port = 0);

    bool operator==(const InetAddress& rhs) const
    {
        return saddr_.sin_family == rhs.saddr_.sin_family
               && ipNetEndian() == rhs.ipNetEndian()
               && portNetEndian() == rhs.portNetEndian();
    }

private:
    static bool resolveSlow(const char* hostname, InetAddress *);

    struct sockaddr_in saddr_;
};

#endif //PNP_INETADDRESS_H
