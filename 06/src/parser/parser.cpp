#include "std_lib_facilities.h"
#include "calculator/parser/parser.h"

namespace calculator::parser {

double Parser::primary()
{
  token_stream::Token token = tstream.get();
  switch (token.kind)
  {
  case '(':
  {
    double d = expression();
    token = tstream.get();
    if (token.kind != ')')
    {
      error("'(' expected");
    }
    return d;
  }

  case '-':
    return -primary();
  case '+':
    return +primary();

  case token_stream::number:
    return token.value;

  case token_stream::name:
    return symb_table.get(token.name);

  default:
    error("primary expected: ", (char)token.kind);
  }
}

double Parser::term()
{
  double left = primary();

  while (true)
  {
    token_stream::Token token = tstream.get();

    switch (token.kind)
    {
    case '*':
      left *= primary();
      break;

    case '/':
    {
      double right = primary();
      if (right == 0)
      {
        error("divide by zero");
      }
      left /= right;
      break;
    }

    default:
      tstream.putback(token);
      return left;
    }
  }
}

double Parser::expression()
{
  double left = term();

  while (true)
  {
    token_stream::Token token = tstream.get();

    switch (token.kind)
    {
    case '+':
      left += term();
      break;

    case '-':
      left -= term();
      break;

    default:
      tstream.putback(token);
      return left;
    }
  }
}

double Parser::declaration(bool is_const = false)
{

  if (is_const)
  {
    token_stream::Token token = tstream.get();
    if (token.kind != token_stream::let)
    {
      tstream.putback(token);
      error("let expected in declaration");
    }
  }

  token_stream::Token token = tstream.get();
  if (token.kind != token_stream::name)
  {
    tstream.putback(token);
    error("name expected in declaration");
  }

  string name = token.name;
  token = tstream.get();
  if (token.kind != '=')
  {
    tstream.putback(token);
    error("'=' missing in declaration of ", name);
  }

  if (symb_table.is_declared(name))
  {
    if (is_const)
    {
      error(name, " declared twice");
    }
    return symb_table.set(name, expression());
  }

  return symb_table.define(name, expression(), is_const);
}

double Parser::statement()
{
  token_stream::Token token = tstream.get();
  switch (token.kind)
  {
  case token_stream::let:
    return declaration();
  case token_stream::user_const:
    return declaration(true);
  default:
    tstream.putback(token);
    return expression();
  }

  error("Somthing went wrong :(");
}

void Parser::start_parse_loop()
{
  while (true)
    try
    {
      cout << token_stream::prompt;
      token_stream::Token token = tstream.get();
      while (token.kind == token_stream::print)
      {
        token = tstream.get();
      }

      if (token.kind == token_stream::quit)
      {
        return;
      }
      if (token.kind == token_stream::help)
      {
        cout << "You don`t need any help!" << endl;
        continue;
      }

      tstream.putback(token);

      double result_expression = statement();
      cout << token_stream::result << result_expression << endl;
      continue;
    }
    catch (runtime_error& e)
    {
      clean_up_mess();
      cerr << "[ERROR]: " << e.what() << endl;
    }
}

void Parser::clean_up_mess() { tstream.ignore(";\n"); }

}  // namespace Parser