#ifndef CPPATCH_UTILS_H
#define CPPATCH_UTILS_H

#ifdef DEBUG_MACRO
#include <iostream>
#include <cstdlib>
#define DEBUG_LOG(x) { std::cerr << x << std::endl; }
#else
#define DEBUG_LOG(x) {}
#endif

#endif // CPPATCH_UTILS_H
