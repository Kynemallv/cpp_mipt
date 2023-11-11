#include <calculator/parser/token_stream/token_stream.h>
#include <std_lib_facilities.h>

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
  if (input == nullptr)
  {
    error("nullptr");
  }

  if (full)
  {
    full = false;
    return buffer;
  }

  char ch;
  input->get(ch);

  if (input->eof())
  {
    return Token{quit};
  }

  switch (ch)
  {
  case '\n':
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

    input->putback(ch);
    double val;
    *input >> val;
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
      while (input->get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
      {
        s += ch;
      }
      input->putback(ch);

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

  putback(buffer);
  return;
}

}  // namespace calculator::parser::token_stream