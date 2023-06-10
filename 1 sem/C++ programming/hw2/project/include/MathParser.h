#pragma once

#include <memory>
#include <string>

#include "AstNode.h"
#include "ParserHelp.h"

class MathParser {
 private:
  ParserHelp parsStr;

 public:
  MathParser() = default;
  explicit MathParser(const std::string& str);
  std::shared_ptr<AstNode> Parse();
  std::shared_ptr<AstNode> Result();
  std::shared_ptr<AstNode> Add();
  std::shared_ptr<AstNode> Mult();
  std::shared_ptr<AstNode> Group();
  std::shared_ptr<AstNode> NUMBER();
};
