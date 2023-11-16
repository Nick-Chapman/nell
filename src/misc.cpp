
#include "misc.h"

void panic(const std::string& file, int line, const std::string& function) {
  printf("**panic(%s:%d): %s\n", file.c_str(), line, function.c_str());
  fflush(stdout);
  abort(); // "crash" macro wrapper will add this anyway
}
