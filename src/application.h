#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <memory>

// user-defined headers
#include "socket.h"


class Application {
    std::unique_ptr<Socket> socket;
public:
    Application();
    virtual int run() = 0;
};

#endif // _APPLICATION_H