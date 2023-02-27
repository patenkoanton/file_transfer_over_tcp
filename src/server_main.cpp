#include <memory>

// user-defined headers
#include "server_main.h"
#include "server.h"

int main()
{
    auto server = std::make_unique<Server>();
    return server->run();
}