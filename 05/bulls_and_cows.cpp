#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using vuint = vector<unsigned int>;
using uint = unsigned int;

int CountBulls (vuint vnumber, vuint vguess)
{
  uint count = 0;
  for (int i = 0; i < vguess.size(); ++i)
    if (vguess[i] == vnumber[i])
      ++count;

  return count;
}

template <typename T> bool InVector (vector<T> vec, T item)
{
  bool res = find(vec.begin(), vec.end(), item) != vec.end();
  return res;
}

int CountCows (vuint vnumber, vuint vguess)
{
  uint count = 0;
  for (int i = 0; i < vguess.size(); ++i)
    if (InVector(vnumber, vguess[i]) && (vnumber[i] != vguess[i]))
      ++count;

  return count;
}

bool CheckDuplicates (vuint vec)
{
  vuint copy(vec);
  sort(copy.begin(), copy.end());

  for (int i = 0; i < copy.size(); ++i)
    if (copy[i] == copy[i + 1])
      return false;

  return true;
}

vuint InputGuess ()
{
  uint count = 0;
  vuint guess;

  cout << "Enter the number: ";
  for (uint digit; cin >> digit;)
  {
    guess.push_back(digit);
    ++count;

    if (count == 4)
    {
      if (!CheckDuplicates(guess))
        return vuint{};
      return guess;
    }
  }

  cin.clear();
  cin.ignore(1000, '\n');
  return vuint{};
}

void Game (vuint number)
{
  for (vuint guess = InputGuess(); guess != number; guess = InputGuess())
  {
    if (guess.size() == 0)
      cout << "This is not valid number!!!" << endl;
    else
    {
      uint bulls = CountBulls(number, guess);
      uint cows = CountCows(number, guess);
      cout << "Bulls: " << bulls << " Cows: " << cows << endl;
    }
  }

  cout << "You Won!!!" << endl;
}

int main (void)
{
  try
  {
    vuint number{1, 2, 3, 4};
    Game(number);
    return 0;
  }
  catch (...)
  {
    cout << "Fuck! This broke";
    return 1;
  }
}
