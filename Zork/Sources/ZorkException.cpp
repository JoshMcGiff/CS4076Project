
#include "iostream"
#include "ZorkException.hpp"

namespace Game {

ZorkException::ZorkException(const std::string &message) noexcept 
: message(message) {
    //std::cout << this->message << std::endl;
}

const char* ZorkException::what() const noexcept {
    return this->message.c_str();
}

}