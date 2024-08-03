#ifndef UTILITY_H
#define UTILITY_H

#include <dlfcn.h>
#include <stddef.h>

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

#define STRINGIFY(x) #x

// convert symbol name to function pointer name
#define FUNC_PTR(_symbol) __wrapper_##_symbol

// common macro to define wrapper function
#define DEFINE_WRAPPER_FUNC_COMMON(_prefix, _symbol, _ret, ...)                \
	static _ret (*FUNC_PTR(_symbol))(__VA_ARGS__) = NULL;                  \
	extern _ret _prefix##_symbol(__VA_ARGS__)

#define LOAD_FUNC_PTR_COMMON(_prefix, _handle, _symbol)                        \
	do {                                                                   \
		FUNC_PTR(_symbol) =                                            \
			dlsym(_handle, STRINGIFY(_prefix##_symbol));           \
		if (UNLIKELY(!FUNC_PTR(_symbol))) {                            \
		}                                                              \
	} while (0)

#endif /* UTILITY_H */
