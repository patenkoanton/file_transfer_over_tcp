#include <memory>

// user-defined headers
#include "client_main.h"
#include "client.h"

int main()
{
    auto client = std::make_unique<Client>();
    return client->run();
}