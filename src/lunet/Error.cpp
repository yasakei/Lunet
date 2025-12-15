#include <iostream>
#include "Error.h"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

Error::Error(std::string errorName_, char details_) {
    errorName = errorName_;
    details = details_;
}

IllegalCharacterError::IllegalCharacterError(char details) {
    error = Error("Illegal Character", details);
}

std::string IllegalCharacterError::Get() {
    return fmt::format("{}:{}", errorName, details);
}