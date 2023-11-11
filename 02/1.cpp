#include <iostream>

int fibonacci (int n)
{
  int fib1 = 1;
  int fib2 = 1;
  int res = 0;

  while (n - 2 > 0)
  {
    res = fib1 + fib2;
    fib2 = fib1;
    fib1 = res;

    --n;
  }

  return res;
}

int main (void)
{
  int n, res;
  std::cout << "Enter n for fibonacci number: ";
  std::cin >> n;

  res = fibonacci(n);
  std::cout << "Fibonacci number "
            << "(" << n << ")"
            << " = " << res << std::endl;

  return 0;
}
