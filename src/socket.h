#ifndef _SOCKET_H
#define _SOCKET_H

#include <memory>

// user-defined headers
#include "ip_address.h"

class Socket {
    int socket_handle = 0;
    int open_socket();
    void close_socket();

public:
    Socket();
    ~Socket();

    // used by client
    int connect_to_ip(const IPAddress &ip, uint16_t port) const;

    // used by server
    int bind_to_ip(const IPAddress &ip, uint16_t port) const;
    int listen_to_client(int max_clients) const;
    int accept_client(IPAddress &client_ip, bool non_blocking = false) const;
};

#endif // _SOCKET_H