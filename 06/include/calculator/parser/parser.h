#ifndef PARSER_H
#define PARSER_H

#include "calculator/parser/token_stream/token_stream.h"
#include "calculator/symbol_table/symbol_table.h"

namespace calculator::parser {

class Parser
{
public:
  Parser() = default;

  Parser(calculator::symbol_table::SymbolTable st) : symb_table{st} {}

  void start_parse_loop ();

  void clean_up_mess ();

private:
  calculator::parser::token_stream::TokenStream tstream;
  calculator::symbol_table::SymbolTable symb_table;

  double primary ();
  double term ();
  double expression ();
  double declaration (bool is_const);
  double statement ();
};

}  // namespace calculator::parser

#endif  // PARSER_H