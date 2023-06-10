#pragma once
#include <memory>

#include "ICalculator.h"

struct NumberT : ICalculatable {
 private:
  double num;

 public:
  NumberT() = default;
  explicit NumberT(double val);
  double Calculate() override;
  double operator+(const NumberT &other);
  double operator-(const NumberT &other);
  double operator*(const NumberT &other);
};

struct Plus : ICalculatable {
 private:
  std::unique_ptr<ICalculatable> a;
  std::unique_ptr<ICalculatable> b;

 public:
  Plus() = default;
  explicit Plus(std::unique_ptr<ICalculatable> a, std::unique_ptr<ICalculatable> b);
  double Calculate() override;
};

struct Minus : ICalculatable {
 private:
  std::unique_ptr<ICalculatable> a;
  std::unique_ptr<ICalculatable> b;

 public:
  Minus() = default;
  explicit Minus(std::unique_ptr<ICalculatable> a, std::unique_ptr<ICalculatable> b);
  double Calculate() override;
};

struct Multiply : ICalculatable {
 private:
  std::unique_ptr<ICalculatable> a;
  std::unique_ptr<ICalculatable> b;

 public:
  Multiply() = default;
  explicit Multiply(std::unique_ptr<ICalculatable> a, std::unique_ptr<ICalculatable> b);
  double Calculate() override;
};

struct MyLn : ICalculatable {
 private:
  std::unique_ptr<ICalculatable> a;

 public:
  MyLn() = default;
  explicit MyLn(std::unique_ptr<ICalculatable> a);
  double Calculate() override;
};

struct MySin : ICalculatable {
 private:
  std::unique_ptr<ICalculatable> a;

 public:
  MySin() = default;
  explicit MySin(std::unique_ptr<ICalculatable> a);
  double Calculate() override;
};
