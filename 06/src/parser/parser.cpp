#include <calculator/parser/parser.h>
#include <std_lib_facilities.h>

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
      error("')' expected");
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
    error("primary expected: ", token.kind);
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

    case token_stream::print:
      return left;

    default:
      tstream.putback(token);
      return left;
    }
  }
}

double Parser::declare(bool is_const = false)
{
  if (is_const)
  {
    token_stream::Token token = tstream.get();

    if (token.kind != token_stream::let)
    {
      tstream.putback(token);
      error("let expected in const declaration");
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
    error("'=' expected in declaration");
  }

  if (symb_table.is_declared(name))
  {
    if (is_const)
    {
      tstream.putback(token);
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
    return declare();
  case token_stream::user_const:
    return declare(true);
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
      if (output == nullptr)
      {
        error("nullptr");
      }

      token_stream::Token token = tstream.get();

      if (input == &cin && token.kind == token_stream::end_line)
      {
        *output << token_stream::prompt;
      }

      while (token.kind == token_stream::print ||
             token.kind == token_stream::end_line)
      {
        token = tstream.get();
      }

      if (token.kind == token_stream::quit)
      {
        return;
      }
      if (token.kind == token_stream::help)
      {
        *output << "You don`t need any help!" << endl;
        continue;
      }

      tstream.putback(token);

      double result_expression = statement();

      *output << token_stream::result << result_expression << endl;
      continue;
    }
    catch (runtime_error& e)
    {
      clean_up_mess();
      *output << "[ERROR]: " << e.what() << endl;
    }
}

}  // namespace calculator::parser