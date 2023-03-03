#include <iostream>
#include <cstring>      // std::strerror()
#include <memory>
#include <sys/socket.h>
#include <unistd.h>     // close()
#include <netdb.h>      // getprotobyname()

// user-defined headers
#include "socket.h"


Socket::Socket()
{
    if (this->open_socket() < 0) {
        throw std::string("failed to open socket.");
    }
}


Socket::~Socket()
{
    this->close_socket();
}


// Used by client
int Socket::connect_to_ip(const IPAddress &ip, uint16_t port) const
{
    const sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = *(ip.to_addr()),
    };

    int rc = connect(this->socket_handle, (const sockaddr *)&address, sizeof(address));
    if (rc < 0) {
        std::cerr << "*ERROR* Failed to connect: " << std::strerror(errno);
        std::cerr << std::endl;
    }

    return rc;
}

// Used by server
int Socket::bind_to_ip(const IPAddress &ip, uint16_t port) const
{
    const sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = *(ip.to_addr()),
    };

    int rc = bind(this->socket_handle, (const sockaddr *)&address, sizeof(address));
    if (rc < 0) {
        std::cerr << "*ERROR* Failed to bind(): " << std::strerror(errno);
        std::cerr << std::endl;
    }

    return rc;
}


// Used by server
int Socket::listen_to_client(int max_clients) const
{
    int rc = listen(this->socket_handle, max_clients);
    if (rc < 0) {
        std::cerr << "*ERROR* Failed to listen(): " << std::strerror(errno);
        std::cerr << std::endl;
    }

    return rc;
}


// Used by server.
//
// On success returns positive number which is client descriptor.
// If the socket is marked nonblocking and no connections are present - returns 0.
// On error returns negative number.
int Socket::accept_client(IPAddress &client_ip, bool non_blocking) const
{
    sockaddr_in client_address;
    auto client_address_size = sizeof(client_address);
    int flags = (non_blocking ? SOCK_NONBLOCK : 0);

    int rc = accept4(this->socket_handle, (sockaddr *)&client_address, (socklen_t *)&client_address_size, flags);
    if (rc < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        }

        std::cerr << "*ERROR* Failed to accept() connection: " << std::strerror(errno);
        std::cerr << std::endl;
    } else {
        // fill in client's IP before returning
        auto client_ip_network_order = *(uint32_t *)&client_address.sin_addr;
        client_ip = ntohl(client_ip_network_order);
    }

    return rc;
}


int Socket::open_socket()
{
    auto protocol = getprotobyname("TCP");
    if (protocol == NULL) {
        std::cerr << "*ERROR* Failed to get TCP protocol info." << std::endl;
        return -1;
    }

    this->socket_handle = socket(AF_INET, SOCK_STREAM, protocol->p_proto);
    if (this->socket_handle < 0) {
        std::cerr << "*ERROR* Failed to create socket: " << std::strerror(errno) << ". ";
        return -1;
    }

    return 0;
}


void Socket::close_socket()
{
    if (close(this->socket_handle) < 0) {
        std::cout << "WARNING: failed to close socket: " << std::strerror(errno) << ".";
        std::cout << std::endl;
    }
}
