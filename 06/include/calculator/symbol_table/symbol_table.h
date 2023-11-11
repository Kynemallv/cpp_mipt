#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <std_lib_facilities.h>

namespace calculator::symbol_table {

struct Variable
{
  string name;
  double value;
  bool is_const{false};

  Variable(string name, double value) : name{name}, value{value} {}

  Variable(string name, double value, bool is_const)
      : name{name}, value{value}, is_const{is_const}
  {
  }
};

class SymbolTable
{
public:
  SymbolTable() = default;

  SymbolTable(vector<Variable> vt) : var_table{vt} {}

  double get (string name);
  double set (string name, double value);
  bool is_declared (string name);
  double define (string name, double value, bool is_const);

private:
  vector<Variable> var_table;
};

}  // namespace SymbleTable

#endif  // SYMBOL_TABLE_H