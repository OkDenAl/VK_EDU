#include "Tokens.h"

#include "cmath"

NumberT::NumberT(double val) : num(val) {}

double NumberT::Calculate() { return num; }

double NumberT::operator+(const NumberT &other) { return num + other.num; }
double NumberT::operator-(const NumberT &other) { return num - other.num; }
double NumberT::operator*(const NumberT &other) { return num * other.num; }

Plus::Plus(std::unique_ptr<ICalculatable> a, std::unique_ptr<ICalculatable> b)
    : a(std::move(a)), b(std::move(b)) {}

double Plus::Calculate() { return a->Calculate() + b->Calculate(); }

Minus::Minus(std::unique_ptr<ICalculatable> a, std::unique_ptr<ICalculatable> b)
    : a(std::move(a)), b(std::move(b)) {}

double Minus::Calculate() { return a->Calculate() - b->Calculate(); }

Multiply::Multiply(std::unique_ptr<ICalculatable> a,
                   std::unique_ptr<ICalculatable> b)
    : a(std::move(a)), b(std::move(b)) {}

double Multiply::Calculate() { return a->Calculate() * b->Calculate(); }

MySin::MySin(std::unique_ptr<ICalculatable> a) : a(std::move(a)) {}

double MySin::Calculate() { return sin(a->Calculate()); }

MyLn::MyLn(std::unique_ptr<ICalculatable> a) : a(std::move(a)) {}

double MyLn::Calculate() { return log(a->Calculate()); }
