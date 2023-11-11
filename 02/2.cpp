#include <iostream>

int lenInt (int n)
{
  int len = 0;
  while (n > 0)
  {
    n /= 10;
    ++len;
  }

  return len;
}

int powInt (int a, int b)
{
  if (b == 0)
    return 1;

  int res = 1;
  for (int i = 0; i < b; ++i)
    res *= a;

  return res;
}

int reverse (int n)
{
  int nReversed = 0;
  int lenNum = lenInt(n);

  for (int i = 1; n > 0; n /= 10)
  {
    nReversed += (n % 10) * powInt(10, (lenNum - i));
    ++i;
  }

  return nReversed;
}

int main (void)
{
  int n, nReversed;
  std::cout << "Enter the num: ";
  std::cin >> n;

  nReversed = reverse(n);
  std::cout << "The reversed num is: " << nReversed;

  return 0;
}