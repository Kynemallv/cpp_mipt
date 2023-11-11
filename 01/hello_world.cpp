#include <iostream>
#include <fstream>

int main (void)
{
  std::ifstream file;
  file.open("data.txt");

  if (file.is_open())
  {
    std::istream* temp = &file;
    std::istream* file_ptr{temp};
    char ch;
    file_ptr->get(ch);

    std::cout << ch;
  }
}
