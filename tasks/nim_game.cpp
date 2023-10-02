#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

enum players
{
  user,
  bot,
  undefined
};

struct GameSession
{
  vector<u_int> state;
  u_int current_turn;
  players current_player;
  players winer;

  GameSession()
      : state{3, 4, 5}, current_player{players(rand() % 2)},
        current_turn{0}, winer{undefined} {};

  GameSession(vector<u_int> initial_state)
      : state{initial_state}, current_player{players(rand() % 2)},
        current_turn{0}, winer{undefined} {};

  GameSession(vector<u_int> initial_state, players initial_player)
      : state{initial_state}, current_player{initial_player},
        current_turn{0}, winer{undefined} {};
};

u_int VectorElemSum (vector<u_int> vec)
{
  u_int res = 0;
  for (u_int i : vec)
    res += i;

  return res;
}

u_int VectorElemXOR (vector<u_int> vec)
{
  u_int res = 0;
  for (u_int i : vec)
    res ^= i;

  return res;
}

u_int FindVecMax (vector<u_int> vec)
{
  u_int max_val = 0;

  for (int i : vec)
    if (i > max_val)
    {
      max_val = i;
    }
  
  return max_val;
}

void RandomMove (GameSession& game)
{
  for (int i = 0; i < game.state.size(); ++i)
    if (game.state[i] != 0)
    {
      --game.state[i];
      break;
    }
}

void BestMove (GameSession& game, u_int curr_nim_sum)
{
  for (int i = 0; i < game.state.size(); ++i)
  {
    if ((game.state[i] ^ curr_nim_sum) < game.state[i])
    {
      game.state[i] ^= curr_nim_sum;
      break;
    }
  }
}

void MakeBotMove (GameSession& game)
{
  u_int curr_nim_sum = VectorElemXOR(game.state);

  if (curr_nim_sum != 0)
  {
    BestMove(game, curr_nim_sum);
  }
  else
  {
    RandomMove(game);
  }
}

vector<u_int> UserInput ()
{
  u_int count = 0;
  vector<u_int> input{};

  for (uint digit = 0; cin >> digit;)
  {
    if (digit & (1 << (sizeof(u_int) * 8) - 1))
    {
      break;
    }

    input.push_back(digit);
    ++count;

    if (count == 2)
    {
      return input;
    }
  }

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Please, enter valid input: ";
  return UserInput();
}

void MakeUserMove (GameSession& game)
{
  vector<u_int> input = UserInput();
  --input[0];
  // std::pair<uint, uint>

  if ((input[0] <= game.state.size()) && (input[1] <= game.state[input[0]]))
  {   
    game.state[input[0]] -= input[1];
    return;
  }
   cout << "Please, enter valid input: ";
   MakeUserMove(game);
}

string operator* (string a, u_int count)
{
  string output = "";
  while (count--)
  {
    output += a;
  }
  return output;
}

void GracefullPrint (GameSession& game)
{
  cout << '\n'
       << "Line" << string{" "} * FindVecMax(game.state) * 2 << "Quantity"
       << endl;
  for (int i = 0; i < game.state.size(); ++i)
  {
    string chip_string = string{"\u25A1 "} * game.state[i];
    cout << setw(2) << i + 1 << string{" "} * 4 << chip_string
         << setw((FindVecMax(game.state) - game.state[i]) * 2 + 3)
         << game.state[i] << endl;
  }

  cout << '\n';
}

void PrintTurnLine (GameSession& game)
{
  string current_player;
  switch (game.current_player)
  {
  case bot:
    current_player = "Bot";
    break;
  case user:
    current_player = "User";
    break;
  default:
    current_player = "Undefined";
    break;
  }
  cout << "===Turn " << game.current_turn << ": " << current_player
       << "===" << endl;
}

void PrintWinerLine (players player)
{
  string winer;
  switch (player)
  {
  case bot:
    winer = "Bot";
    break;
  case user:
    winer = "User";
    break;
  default:
    winer = "Undefined";
    break;
  }

  cout << winer << " won!!!" << endl;
}

void StartGame (vector<u_int> initial_state, players initial_player)
{
  srand(time(NULL));

  GameSession game = GameSession{initial_state, initial_player};
  GracefullPrint(game);

  while (VectorElemSum(game.state) > 0)
  {
    PrintTurnLine(game);
    if (game.current_player == bot)
    {
      cout << "Bot is thinking" << flush;
      sleep(1);
      cout << "." << flush;
      sleep(1);
      cout << "." << flush;
      sleep(1);
      cout << "." << endl;
      MakeBotMove(game);
    }
    else
    {
      cout << "Enter line and number: ";
      MakeUserMove(game);
    }

    ++game.current_turn;
    GracefullPrint(game);
    game.current_player = players((game.current_player + 1) % 2);
  }

  game.winer = players((game.current_player + 1) % 2);
  PrintWinerLine(game.winer);
}

int main (void)
{
  try
  {
    vector<u_int> initial_state{3, 4, 5};
    players initial_player{user};
    StartGame(initial_state, initial_player);
  }
  catch (const exception& e)
  {
    cerr << "Somthing strange error!" << '\n' << e.what() << endl;
    return -1;
  }

  return 0;
}