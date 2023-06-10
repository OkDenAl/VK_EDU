#include "AstNode.h"

#include <algorithm>
#include <iostream>
#include <type_traits>

#include "AstNodeType.h"
#include "Exeptions.h"

AstNode::AstNode(int type, const std::string &text)
    : type_(std::move(type)),
      text_(std::move(text)),
      parent_(std::weak_ptr<AstNode>()) {
  GlobalIdForASTNode++;
}

std::shared_ptr<AstNode> AstNode::GetNewInstance(
    int type, std::unique_ptr<ICalculatable> data, const std::string &text,
    const std::shared_ptr<AstNode> &child1,
    const std::shared_ptr<AstNode> &child2) {
  std::shared_ptr<AstNode> instance =
      std::make_shared<AstNode>(AstNode(std::move(type), std::move(text)));
  instance->SetData(std::move(data));
  if (child1) {
    instance->AddChild(child1);
  }
  if (child2) {
    instance->AddChild(child2);
  }
  return instance;
}

std::shared_ptr<AstNode> AstNode::GetNewInstance(
    int type, std::unique_ptr<ICalculatable> data, const std::string &text) {
  return GetNewInstance(type, std::move(data), text, std::shared_ptr<AstNode>(),
                        std::shared_ptr<AstNode>());
}

void AstNode::AddChild(const std::shared_ptr<AstNode> &child) {
  auto self = this->shared_from_this();
  child->SetParent(self);
  childs_.emplace_back(std::move(child));
}

int AstNode::GetChildsCount() { return childs_.size(); }

std::shared_ptr<AstNode> AstNode::GetChild(int index) {
  return *(std::next(childs_.begin(), index));
}

std::weak_ptr<AstNode> AstNode::GetParent() { return parent_; }

void AstNode::SetParent(const std::weak_ptr<AstNode> &parent) {
  parent_ = parent;
}

std::string AstNode::GetUniqueName() { return uniqName_; }

std::string AstNode::GetText() { return text_; }

int AstNode::GetType() { return type_; }

std::unique_ptr<ICalculatable> AstNode::GetData() { return std::move(data_); }

void AstNode::SetData(std::unique_ptr<ICalculatable> data) {
  data_ = std::move(data);
}
