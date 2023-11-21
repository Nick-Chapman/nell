#ifndef MISC_H
#define MISC_H

#include <string>

#define up std::unique_ptr
#define mv std::move
#define mk std::make_unique

void panic(const std::string& file, int line, const std::string& function);
void traceF(const std::string& file, int line, const std::string& function);

#define crash { panic(__FILE__, __LINE__, __PRETTY_FUNCTION__); abort(); }
#define trace { traceF(__FILE__, __LINE__, __PRETTY_FUNCTION__); }

#endif //MISC_H
