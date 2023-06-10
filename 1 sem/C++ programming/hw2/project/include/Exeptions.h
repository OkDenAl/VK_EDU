#pragma once

#include <exception>
#include <string>

struct InvalidExpressionException : public std::exception {
 public:
  explicit InvalidExpressionException(const std::string& msg);
  const char* what() const noexcept;

 private:
  std::string message;
};
