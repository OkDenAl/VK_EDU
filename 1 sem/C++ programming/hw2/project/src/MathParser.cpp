#include "MathParser.h"

#include <iostream>

#include "AstNodeType.h"
#include "Exeptions.h"
#include "Tokens.h"

MathParser::MathParser(const std::string& str) { parsStr = ParserHelp(str); }

std::shared_ptr<AstNode> MathParser::Parse() {
  parsStr.SkipSpaces();
  std::shared_ptr<AstNode> res = Result();

  if (parsStr.End()) {
    return res;
  } else {
    throw InvalidExpressionException(std::to_string(parsStr.GetPos()));
  }
}

std::shared_ptr<AstNode> MathParser::Result() { return Add(); }

std::shared_ptr<AstNode> MathParser::Add() {
  std::shared_ptr<AstNode> res = Mult();
  std::string oper;

  while (true) {
    if (parsStr.IsMatch("+")) {
      oper = parsStr.MatchToken("+").first;
    } else if (parsStr.IsMatch("-")) {
      oper = parsStr.MatchToken("-").first;
    } else {
      break;
    }
    std::shared_ptr<AstNode> temp = Mult();
    if (oper == "+") {
      res = AstNode::GetNewInstance(
          AstNodeType::Add,
          std::make_unique<Plus>(Plus(res->GetData(), temp->GetData())), "PLUS",
          res, temp);
    } else {
      res = AstNode::GetNewInstance(
          AstNodeType::Sub,
          std::make_unique<Minus>(Minus(res->GetData(), temp->GetData())),
          "MINUS", res, temp);
    }
  }
  return res;
}

std::shared_ptr<AstNode> MathParser::Mult() {
  std::shared_ptr<AstNode> res = Group();
  while (parsStr.IsMatch("*")) {
    parsStr.MatchToken("*");
    std::shared_ptr<AstNode> temp = Group();
    res = AstNode::GetNewInstance(
        AstNodeType::Mult,
        std::make_unique<Multiply>(Multiply(res->GetData(), temp->GetData())),
        "MUL", res, temp);
  }
  return res;
}

std::shared_ptr<AstNode> MathParser::Group() {
  std::shared_ptr<AstNode> res;
  if (parsStr.IsMatch("sin")) {
    parsStr.MatchToken("sin");
    auto temp = Add();
    res = AstNode::GetNewInstance(
        AstNodeType::Sin, std::make_unique<MySin>(MySin(temp->GetData())),
        "SIN", temp, std::shared_ptr<AstNode>());
    return res;
  }
  if (parsStr.IsMatch("ln")) {
    parsStr.MatchToken("ln");
    auto temp = Add();
    res = AstNode::GetNewInstance(AstNodeType::Ln,
                                  std::make_unique<MyLn>(MyLn(temp->GetData())),
                                  "LN", temp, std::shared_ptr<AstNode>());
    return res;
  }
  if (parsStr.IsMatch("(")) {
    parsStr.MatchToken("(");
    res = Add();
    if (!parsStr.MatchToken(")").second) {
      throw InvalidExpressionException(std::to_string(parsStr.GetPos()));
    }
    return res;
  }
  return NUMBER();
}

std::shared_ptr<AstNode> MathParser::NUMBER() {
  std::string number = "";
  while (parsStr.CurSymbol() == '.' || std::isdigit(parsStr.CurSymbol())) {
    number += parsStr.CurSymbol();
    parsStr.Next();
  }
  parsStr.SkipSpaces();
  if (number.length() == 0) {
    throw InvalidExpressionException(std::to_string(parsStr.GetPos()));
  }
  return AstNode::GetNewInstance(
      AstNodeType::Number,
      std::make_unique<NumberT>(NumberT(std::stod(number))), number);
}
