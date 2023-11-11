#ifndef PARSER_H
#define PARSER_H

#include <calculator/parser/token_stream/token_stream.h>
#include <calculator/symbol_table/symbol_table.h>

#include <iostream>

namespace calculator::parser {

class Parser
{
public:
  Parser()
  {
    input = &cin;
    output = &cout;

    if (input != nullptr)
      tstream = calculator::parser::token_stream::TokenStream{input};
    else
      error("nullptr");
  }

  Parser(calculator::symbol_table::SymbolTable st) : symb_table{st}
  {
    input = &cin;
    output = &cout;

    if (input != nullptr)
      tstream = calculator::parser::token_stream::TokenStream{input};
    else
      error("nullptr");
  }

  Parser(calculator::symbol_table::SymbolTable st,
         std::istream* input_stream)
      : symb_table{st}, input{input_stream}
  {
    output = &cout;

    if (input != nullptr)
      tstream = calculator::parser::token_stream::TokenStream{input};
    else
      error("nullptr");
  }

  Parser(calculator::symbol_table::SymbolTable st,
         std::istream* input_stream, std::ostream* output_stream)
      : symb_table{st}, input{input_stream}, output{output_stream}
  {
    if (input != nullptr)
      tstream = calculator::parser::token_stream::TokenStream{input};
    else
      error("nullptr");
  }

  void start_parse_loop ();

  void clean_up_mess () { tstream.ignore(";\n"); }

private:
  calculator::parser::token_stream::TokenStream tstream;
  calculator::symbol_table::SymbolTable symb_table;

  std::istream* input;
  std::ostream* output;

  double primary ();
  double term ();
  double expression ();
  double declare (bool is_const);
  double statement ();
};

}  // namespace calculator::parser

#endif  // PARSER_H