#ifndef ZORKEXCEPTION_HPP
#define ZORKEXCEPTION_HPP

#include <exception>
#include <string>

namespace Game {

    class ZorkException : public std::exception {
    public:
        ZorkException(const std::string &message) noexcept;
        virtual ~ZorkException() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string message;
    };

} //namespace Game

#endif