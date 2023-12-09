#pragma once
#include <string>

class Tracer
{
  public:
    Tracer(const std::string& func, const std::string& file, int line);
    ~Tracer();

  private:
    std::string mess;
    static int counter;
    std::string indent () const;
};

#define ENABLE_TRACING 1
#ifdef ENABLE_TRACING
#define TRACE(name)                                                                                \
    Tracer a_tracer_obj { name, __FILE__, __LINE__ }
#else
#define TRACE(name)
#endif
#define TRACE_FUNC                                                                                 \
    Tracer a_tracer_obj { __func__, __FILE__, __LINE__ }