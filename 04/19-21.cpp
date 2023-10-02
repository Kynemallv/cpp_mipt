#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct MyDict
{
  vector<string> names;
  vector<int> scores;

  MyDict() = default;
};

MyDict& ReadData (MyDict& dict)
{
  for (string name; cin >> name;)
  {
    int score;

    if (!(cin >> score))
    {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Please, enter the line like: <Name> <Score>" << endl;
      continue;
    }

    if ((name == "NoName") && (score == 0))
      return dict;

    dict.names.push_back(name);
    dict.scores.push_back(score);
    return dict;
  }
}

bool CheckDuplicates (MyDict& dict)
{
  vector<string> copy(dict.names);
  sort(copy.begin(), copy.end());

  for (int i = 0; i < copy.size(); ++i)
    if (copy[i] == copy[i + 1])
      return false;

  return true;
}

int SearchByName (MyDict& dict, string name)
{
  for (int i = 0; i < dict.names.size(); ++i)
    if (dict.names[i] == name)
      return dict.scores[i];
}

vector<string> SearchByScore (MyDict& dict, int score)
{
  vector<string> res;

  for (int i = 0; i < dict.scores.size(); ++i)
    if (dict.scores[i] == score)
      res.push_back(dict.names[i]);

  return res;
}

void StartSearchLoop (MyDict& dict)
{
  char ans;
  constexpr char by_name = 'n';
  constexpr char by_score = 's';
  constexpr char exit_state = 'e';

  while (cin >> ans)
  {
    switch (ans)
    {
    case by_name:
    {
      string name, res;
      cout << "Enter the name: ";
      cin >> name;
      res = SearchByName(dict, name);
      cout << res << endl;
      break;
    }

    case by_score:
    {
      int score;
      vector<string> res;
      cout << "Enter score: ";
      cin >> score;
      res = SearchByScore(dict, score);
      cout << res.size() << endl;
      break;
    }

    case exit_state:
    {
      cout << "Good Bye";
      exit(0);
    }

    default:
      break;
    }
  }
}

int main (void)
{
  MyDict dict = MyDict{};
  ReadData(dict);

  if (CheckDuplicates(dict))
  {
    cout << "===\n";
    for (int i = 0; i < dict.names.size(); ++i)
      cout << dict.names[i] << " " << dict.scores[i] << endl;
  }
  else
  {
    cout << "Error: Some names were entered twice";
    return 1;
  }

  StartSearchLoop(dict);
}
