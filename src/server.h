#ifndef _SERVER_H
#define _SERVER_H

#include "application.h"


class Server : public Application {
public:
    Server();
    virtual int run();
};

#endif // _SERVER_H