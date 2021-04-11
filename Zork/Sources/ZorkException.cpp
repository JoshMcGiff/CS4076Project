
#include "iostream"
#include "ZorkException.hpp"

namespace Game {

ZorkException::ZorkException(const std::string &message) noexcept //Use exceptions for incase moving happens when not in a world
: message(message) {
    //std::cout << this->message << std::endl;
}

const char* ZorkException::what() const noexcept {
    return this->message.c_str();
}

}