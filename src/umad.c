#include "infiniband/umad.h"
#include "utility.h"

#define DEFINE_WRAPPER_FUNC_UMAD(_symbol, _ret, ...)                           \
	DEFINE_WRAPPER_FUNC_COMMON(umad_, _symbol, _ret, __VA_ARGS__)

#define LOAD_FUNC_PTR_UMAD(_handle, _symbol)                                   \
	LOAD_FUNC_PTR_COMMON(umad_, _handle, _symbol)

static __attribute__((constructor)) void mummy_umad_init(void)
{
}
