#include "ParserHelp.h"

#include <cctype>  // для функции isspace
#include <iostream>

ParserHelp::ParserHelp(const std::string &str) : inp(str), pos(0) {}

bool ParserHelp::End() { return inp.length() <= pos; }

void ParserHelp::Next() {
  if (!End()) {
    pos++;
  }
}

void ParserHelp::SkipSpaces() {
  while (isspace(inp[pos])) {
    Next();
  }
}

char ParserHelp::CurSymbol() {
  if (!End()) {
    return inp[pos];
  }
  return '#';
}

bool ParserHelp::isStringMatch(const std::string &str) {
  for (int i = 0; i < str.length(); i++) {
    if (End() || CurSymbol() != str[i]) {
      return false;
    }
    Next();
  }
  return true;
}

bool ParserHelp::IsMatch(const std::string &str) {
  if (End()) {
    return false;
  }
  SkipSpaces();
  int memPos = pos;
  bool ans = isStringMatch(str);
  pos = memPos;
  return ans;
}

std::pair<std::string, bool> ParserHelp::MatchToken(const std::string &str) {
  if (End()) {
    return std::make_pair(str, false);
  }
  SkipSpaces();
  if (!isStringMatch(str)) {
    return std::make_pair(str, false);
  }
  SkipSpaces();
  return std::make_pair(str, true);
}

int ParserHelp::GetPos() { return pos; }
