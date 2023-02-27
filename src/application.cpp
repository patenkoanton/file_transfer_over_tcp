#include <memory>

// user-defined headers
#include "application.h"


Application::Application()
{
    this->socket = std::make_unique<Socket>();
}