#include <calculator/calculator.h>
#include <fstream>
#include <iostream>

using namespace std;

string InputFileName ()
{
  string filename;

  while (filename.empty())
  {
    cout << "enter a file name: ";
    cin >> filename;
  }

  return filename;
}

bool UseCastomStream (string greating)
{
  char answer{};
  bool state{false};

  while (!state)
  {
    cout << greating;
    cin >> answer;

    switch (answer)
    {
    case 'y':
    {
      try
      {
        return true;
      }
      catch (runtime_error& e)
      {
        cout << e.what() << endl;
      }

      break;
    }

    case 'n':
    {
      return false;
    }

    default:
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      break;
    }
    }
  }

  error("Somthing went wrong!");
}

int main ()
{

  istream* input_stream = &cin;
  ostream* output_stream = &cout;

  try
  {
    calculator::symbol_table::SymbolTable default_symbol_table{};
    default_symbol_table.define("pi", 3.141592653589793, true);
    default_symbol_table.define("e", 2.718281828459045, true);

    ifstream ifile;
    if (UseCastomStream("Do you want to use input file? [y/n]: "))
    {
      string filename = InputFileName();

      ifile.open(filename);
      if (!ifile.is_open())
      {
        error("file not exist");
      }

      input_stream = &ifile;
    }

    ofstream ofile;
    if (UseCastomStream("Do you want to use output file? [y/n]: "))
    {
      string filename = InputFileName();

      ofile.open(filename);
      if (!ofile.is_open())
      {
        error("file not exist");
      }

      output_stream = &ofile;
    }

    calculator::parser::Parser parser{default_symbol_table, input_stream,
                                      output_stream};
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
}
