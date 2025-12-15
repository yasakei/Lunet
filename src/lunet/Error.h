#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
    public:
        Error() = default;
        Error(std::string errorName_, char details_);

    protected:
        std::string errorName;
        char details;
};

class IllegalCharacterError : Error {
    public:
        IllegalCharacterError() = default;
        IllegalCharacterError(char details);
        std::string Get();

    public:
        bool hasError{};

    private:
        Error error;
};

#endif