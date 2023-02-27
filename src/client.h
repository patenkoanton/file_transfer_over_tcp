#ifndef _CLIENT_H
#define _CLIENT_H

#include "application.h"


class Client : public Application
{
public:
    Client();
    virtual int run();
};

#endif // _CLIENT_H