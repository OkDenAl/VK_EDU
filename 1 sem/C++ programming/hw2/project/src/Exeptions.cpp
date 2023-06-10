#include "Exeptions.h"

InvalidExpressionException::InvalidExpressionException(const std::string& msg) {
  message = "Invalid expression syntax in: " + msg + " position\n";
}

const char* InvalidExpressionException::what() const noexcept {
  return message.c_str();
}
