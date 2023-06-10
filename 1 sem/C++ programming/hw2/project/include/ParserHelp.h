#pragma once

#include <string>
#include <utility>

class ParserHelp {
 private:
  std::string inp;
  int pos;
  bool isStringMatch(const std::string &str);

 public:
  ParserHelp() = default;
  explicit ParserHelp(const std::string &str);
  int GetPos();
  bool End();
  void Next();
  void SkipSpaces();
  char CurSymbol();
  bool IsMatch(const std::string &str);
  std::pair<std::string, bool> MatchToken(const std::string &str);
  ~ParserHelp() = default;
};
