#include "tracer.h"
#include <iostream>

int Tracer::counter{0};

std::string Tracer::indent() const
{
    std::string res = "";
    for (int i = 0; i < counter; ++i)
        res += ". ";
    return res;
}

Tracer::Tracer(const std::string& func, const std::string& file, int line) : mess{func}
{
    std::cerr << Tracer::indent() << "IN -> " << mess << " [" << file << ": " << line << "]"
              << std::endl;
    counter++;
}

Tracer::~Tracer()
{
    counter--;
    std::cerr << Tracer::indent() << "OUT <- " << mess << std::endl;
}