#pragma once

#include <list>
#include <memory>
#include <string>

#include "ICalculator.h"

static int GlobalIdForASTNode = 0;

class AstNode : public std::enable_shared_from_this<AstNode> {
 private:
  int type_;
  std::string uniqName_ = "node_" + std::to_string(GlobalIdForASTNode);
  std::unique_ptr<ICalculatable> data_;
  std::string text_;
  std::weak_ptr<AstNode> parent_;
  std::list<std::shared_ptr<AstNode>> childs_;


 public:
  AstNode(int type, const std::string &text);

  static std::shared_ptr<AstNode> GetNewInstance(
      int type, std::unique_ptr<ICalculatable> data, const std::string &text,
      const std::shared_ptr<AstNode> &child1,
      const std::shared_ptr<AstNode> &child2);
  static std::shared_ptr<AstNode> GetNewInstance(
      int type, std::unique_ptr<ICalculatable> data, const std::string &text);

  void AddChild(const std::shared_ptr<AstNode> &child);

  void SetParent(const std::weak_ptr<AstNode> &parent);

  int GetChildsCount();

  void SetData(std::unique_ptr<ICalculatable> data);

  std::string GetUniqueName();

  std::string GetText();

  int GetType();

  std::unique_ptr<ICalculatable> GetData();

  std::shared_ptr<AstNode> GetChild(int index);

  std::weak_ptr<AstNode> GetParent();
};
