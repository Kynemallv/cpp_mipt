#include <cmath>
#include <iostream>
#include <string>

bool isPrime (int n)
{
  int dSum = 0;
  for (int i = 2; i <= sqrt(double(n)); ++i)
    if (n % i == 0)
      dSum += 1;

  return (dSum < 1 && n != 1) ? true : false;
}

int main (void)
{
  int n;
  std::string res;
  std::cout << "Enter the number: ";
  std::cin >> n;

  res = (isPrime(n)) ? "prime" : "not prime";
  std::cout << "This number is " << res << std::endl;

  return 0;
}