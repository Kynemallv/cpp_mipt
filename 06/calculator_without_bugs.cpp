#include "std_lib_facilities.h"
#include "calculator/calculator.h"

int main ()
try
{
  calculator::symbol_table::SymbolTable default_symbol_table{};
  default_symbol_table.define("pi", 3.141592653589793, true);
  default_symbol_table.define("e", 2.718281828459045, true);

  calculator::parser::Parser parser{default_symbol_table};
  parser.start_parse_loop();
}
catch (exception& e)
{
  cerr << "exception: " << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Oops, unknown exception" << endl;
  return 2;
}
