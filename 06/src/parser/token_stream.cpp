#include "std_lib_facilities.h"
#include "calculator/parser/token_stream/token_stream.h"

namespace calculator::parser::token_stream {

void TokenStream::putback(Token t)
{
  if (full)
  {
    error("putback() into a full buffer");
  }

  buffer = t;
  full = true;
}

Token TokenStream::get()
{
  if (full)
  {
    full = false;
    return buffer;
  }

  char ch;
  cin.get(ch);

  switch (ch)
  {
  case '\n':
    return Token{print};

  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case ';':
  case '=':
    return Token{ch};

  case '.':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  {
    cin.putback(ch);
    double val;
    cin >> val;
    return Token{number, val};
  }

  default:
    if (isspace(ch))
    {
      return get();
    }

    if (isalpha(ch) || ch == '_')
    {
      string s;
      s += ch;
      while (cin.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_')
      {
        s += ch;
      }
      cin.putback(ch);

      auto command = commands.find(s);
      if (command != commands.end())
      {
        return Token{command->second};
      }

      return Token{name, s};
    }
    error("Bad token");
  }
}

void TokenStream::ignore(string s)
{
  if (full && s.find(buffer.kind) != string::npos)
  {
    full = false;
    return;
  }
  full = false;

  while (s.find(buffer.kind) == string::npos)
  {
    buffer = get();
  }

  return;
}

}  // namespace TokenStream