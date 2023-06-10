#include <gtest/gtest.h>

#include "ASTNodeWalker.h"
#include "Exeptions.h"
#include "MathParser.h"
#include "ParserHelp.h"

TEST(ParserHelpSkipSpace, SkipSpaceBasicTest) {
  ParserHelp parsHelp("  2");
  parsHelp.SkipSpaces();
  int p = parsHelp.GetPos();
  EXPECT_EQ(p, 2);
}

TEST(ParserHelpSkipSpace, SkipSpaceOnlySpaceStringTest) {
  ParserHelp parsHelp("  ");
  parsHelp.SkipSpaces();
  int p = parsHelp.GetPos();
  EXPECT_EQ(p, 2);
}

TEST(ParserHelpIsMatch, IsMatchWithoutSpacesTestTrue) {
  ParserHelp parsHelp("sin(3)");
  EXPECT_TRUE(parsHelp.IsMatch("sin"));
}

TEST(ParserHelpIsMatch, IsMatchWithoutSpacesTestFalse) {
  ParserHelp parsHelp("sin(3)");
  EXPECT_FALSE(parsHelp.IsMatch("cos"));
}

TEST(ParserHelpIsMatch, IsMatchWithSpacesTestTrue) {
  ParserHelp parsHelp("   sin(3)");
  EXPECT_TRUE(parsHelp.IsMatch("sin"));
}

TEST(ParserHelpMatchToken, MatchTokenWithoutSpacesTest) {
  ParserHelp parsHelp("sin(3)");
  std::string token = parsHelp.MatchToken("sin").first;
  int pos = parsHelp.GetPos();
  EXPECT_EQ(token, "sin");
  EXPECT_EQ(pos, 3);
}

TEST(ParserHelpMatchToken, MatchTokenWithSpacesTest) {
  ParserHelp parsHelp(" sin (3)");
  std::string token = parsHelp.MatchToken("sin").first;
  int pos = parsHelp.GetPos();
  EXPECT_EQ(token, "sin");
  EXPECT_EQ(pos, 5);
}

TEST(BuildASTTree, OKWithPlusAndMinusOperations) {
  auto res = MathParser("23 + 7 - ( 10 + 12 )").Parse();
  ASTNodeWalker walker(res);
  walker.buildDotFormat();
  EXPECT_EQ(walker.getDotFormat(),
            "graph {\n"
            "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];\n"
            "\tsubgraph cluster17{\n"
            "\t\tnnode_6[label=\"MINUS\"];\n"
            "\t\tnnode_2[label=\"PLUS\"];\n"
            "\t\tnnode_6--nnode_2;\n"
            "\t\tnnode_0[label=\"23\"];\n"
            "\t\tnnode_2--nnode_0;\n"
            "\t\tnnode_1[label=\"7\"];\n"
            "\t\tnnode_2--nnode_1;\n"
            "\t\tnnode_5[label=\"PLUS\"];\n"
            "\t\tnnode_6--nnode_5;\n"
            "\t\tnnode_3[label=\"10\"];\n"
            "\t\tnnode_5--nnode_3;\n"
            "\t\tnnode_4[label=\"12\"];\n"
            "\t\tnnode_5--nnode_4;\n"
            "\t}\n"
            "}"
            "\n");
}

TEST(ExecuteMathExpr, OKWithPlusOperations) {
  auto parsed = MathParser("3+4+(5+10)").Parse();
  double res = parsed->GetData()->Calculate();
  EXPECT_EQ(res, 22);
}

TEST(ExecuteMathExpr, OKWithMultiplyOperation) {
  auto parsed = MathParser("3+4*5+5+10-4-3-10*2-5").Parse();
  double res = parsed->GetData()->Calculate();
  EXPECT_EQ(res, 6);
}

TEST(ExecuteMathExpr, OKWithSinOperationWithValue) {
  auto parsed = MathParser("3+sin(0)").Parse();
  double res = parsed->GetData()->Calculate();
  EXPECT_EQ(res, 3);
}

TEST(ExecuteMathExpr, OKWithSinOperationWithExpr) {
  auto parsed = MathParser("3+sin(2-2*(1+0))").Parse();
  double res = parsed->GetData()->Calculate();
  ;
  EXPECT_EQ(res, 3);
}

TEST(ExecuteMathExpr, OKWithLnOperationWithValue) {
  auto parsed = MathParser("3+ln(1)").Parse();
  double res = parsed->GetData()->Calculate();
  EXPECT_EQ(res, 3);
}

TEST(ExecuteMathExpr, OKWithLnOperationWithExpr) {
  auto parsed = MathParser("3+ln(3-2*(1+0))").Parse();
  double res = parsed->GetData()->Calculate();
  EXPECT_EQ(res, 3);
}

TEST(ExecuteMathExpr, OKWithBracketsAndPlusMinus) {
  auto parsed = MathParser("3+4*(5+5)+10-4-3-10*2-5").Parse();
  double res = parsed->GetData()->Calculate();
  ;
  EXPECT_EQ(res, 21);
  parsed = MathParser("3+4*(2+7-3)+5*10").Parse();
  res = parsed->GetData()->Calculate();
  ;
  EXPECT_EQ(res, 77);
}

TEST(ExecuteMathExpr, FailWithBracketsAndPlusMinus) {
  EXPECT_THROW(MathParser("3+4*((5+5)+10*2-5").Parse(),
               InvalidExpressionException);
}

TEST(ExecuteMathExpr, FailWithNotFillExpr) {
  EXPECT_THROW(MathParser("3+").Parse(), InvalidExpressionException);
}

TEST(ExecuteMathExpr, FailWithInvalidSymbol) {
  EXPECT_THROW(MathParser("2+1+4/2").Parse(), InvalidExpressionException);
}

TEST(ExecuteMathExpr, FailWithInvalidSymbolAndBracket) {
  EXPECT_THROW(MathParser("2+)1+4/2").Parse(), InvalidExpressionException);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}