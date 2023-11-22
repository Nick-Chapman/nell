
#include "misc.h"

void panic(const std::string& file, int line, const std::string& function) {
  printf("**PANIC(%s:%d): %s\n", file.c_str(), line, function.c_str());
  fflush(stdout);
  abort(); // "crash" macro wrapper will add this anyway
}

void traceF(const std::string& file, int line, const std::string& function) {
  printf("**trace(%s:%d): %s\n", file.c_str(), line, function.c_str());
}
