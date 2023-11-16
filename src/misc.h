#ifndef MISC_H
#define MISC_H

#include <string>

void panic(const std::string& file, int line, const std::string& function);

#define crash { panic(__FILE__, __LINE__, __PRETTY_FUNCTION__); abort(); }

#endif //MISC_H
