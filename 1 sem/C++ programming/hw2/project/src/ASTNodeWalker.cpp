#include "ASTNodeWalker.h"

#include <iostream>

ASTNodeWalker::ASTNodeWalker(std::shared_ptr<AstNode> head)
    : head_(std::move(head)) {}

void ASTNodeWalker::buildDotFormat() {
  std::stringstream stream;
  stream << "graph {" << std::endl;
  stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];"
         << std::endl;
  stream << "\tsubgraph cluster17{" << std::endl;

  ASTNodeWalker::GetStringSubTree(head_, stream);

  stream << "\t}\n}" << std::endl;
  dotFormat_ = stream.str();
}

std::string ASTNodeWalker::getDotFormat() { return dotFormat_; }

void ASTNodeWalker::GetStringSubTree(const std::shared_ptr<AstNode> &node,
                                     std::stringstream &stream) {
  if (!node->GetParent().lock()) {
    stream << "\t\tn" << node->GetUniqueName() << "[label=\"" << node->GetText()
           << "\"];" << std::endl;
  } else {
    stream << "\t\tn" << node->GetUniqueName() << "[label=\"" << node->GetText()
           << "\"];" << std::endl;
    stream << "\t\tn" << node->GetParent().lock()->GetUniqueName() << "--n"
           << node->GetUniqueName() << ";" << std::endl;
  }

  for (int i = 0; i < node->GetChildsCount(); i++) {
    GetStringSubTree(node->GetChild(i), stream);
  }
}
