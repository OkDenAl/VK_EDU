#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "AstNode.h"

class ASTNodeWalker {
 public:
  explicit ASTNodeWalker(std::shared_ptr<AstNode> head);

  void buildDotFormat();

  std::string getDotFormat();
  void GetStringSubTree(const std::shared_ptr<AstNode> &node,
                        std::stringstream &stream);

 private:
  const std::shared_ptr<AstNode> head_;
  std::string dotFormat_;
};
