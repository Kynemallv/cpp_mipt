#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "std_lib_facilities.h"

namespace calculator::parser::token_stream {

constexpr char print = ';';
constexpr char end_line = '\n';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'l';
constexpr char user_const = 'c';
constexpr char quit = 'q';
constexpr char help = 'h';

const string prompt = "> ";
const string result = "= ";

const map<string, char> commands{
    {"let", let}, {"const", user_const}, {"help", help}, {"quit", quit}};

struct Token
{
  char kind;
  double value;
  string name;

  Token() = default;

  Token(char ch) : kind{ch}, value{0} {}

  Token(char ch, double val) : kind{ch}, value{val} {}

  Token(char ch, string name) : kind{ch}, name{name} {}
};

class TokenStream
{
public:
  TokenStream(){};

  Token get ();
  void putback (Token t);

  void ignore (string s);

private:
  bool full{false};
  Token buffer{'\0'};
};

}  // namespace calculator::parser::token_stream

#endif  // TOKEN_STREAM_H