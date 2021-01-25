
/// Хак, позволяющий выполнять проверки на этапе компиляции
#define DUMB_STATIC_ASSERT(test) typedef char assertion_on_my_struct[(!!(test)) * 2 - 1]

#ifndef NDEBUG
#include <stdio.h>
#define DEBUG(FORMAT_STR, ...) printf("%s:%d %s(): " FORMAT_STR "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else // NDEBUG
#define DEBUG(Fmt, ...)
#endif // NDEBUG
