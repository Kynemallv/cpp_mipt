#include <cmath>
#include <iostream>
#include <tuple>

double factorial (int n)
{
  long double res = 1;
  for (int i = 1; i <= n; ++i)
    res *= i;

  return res;
}

double calculExpr (double eps)
{
  const double expr = (exp(1.0) + exp(-1.0)) / 2.0;
  double res = 1.0;

  for (int k = 1; std::abs(res - expr) > eps; ++k)
  {
    long long int tmp = factorial(2 * k);
    res += 1.0 / factorial(2 * k);
  }

  return res;
}

int main (void)
{
  std::cout.precision(10);

  double eps;
  std::cout << "enter precision: ";
  std::cin >> eps;

  double res;
  res = calculExpr(eps);
  std::cout << (exp(1.0) + exp(-1.0)) / 2.0 << "\n" << res;

  return 0;
}
