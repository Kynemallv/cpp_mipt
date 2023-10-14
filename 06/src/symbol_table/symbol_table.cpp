#include "std_lib_facilities.h"
#include "calculator/symbol_table/symbol_table.h"

namespace calculator::symbol_table {

double SymbolTable::get(string name)
{
  for (int i = 0; i < var_table.size(); ++i)
  {
    if (var_table[i].name == name)
    {
      return var_table[i].value;
    }
  }

  error("get: undefined name ", name);
}

double SymbolTable::set(string name, double value)
{
  for (int i = 0; i < var_table.size(); ++i)
  {
    if (var_table[i].name == name)
    {
      if (var_table[i].is_const)
      {
        error("set: can't set value for const variable");
      }

      var_table[i].value = value;
      return value;
    }
  }

  error("set: undefined name ", name);
}

bool SymbolTable::is_declared(string name)
{
  for (int i = 0; i < var_table.size(); ++i)
  {
    if (var_table[i].name == name)
    {
      return true;
    }
  }

  return false;
}

double SymbolTable::define(string name, double value, bool is_const)
{
  if (is_declared(name))
  {
    error(name, " declared twice");
  }

  var_table.push_back(Variable{name, value, is_const});
  return value;
}

}  // namespace Var