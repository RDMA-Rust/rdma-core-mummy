#include "infiniband/verbs.h"
#include "utility.h"
#include <dlfcn.h>
#include <errno.h>

#define DEFINE_WRAPPER_FUNC_IBV(_symbol, _ret, ...)                            \
	DEFINE_WRAPPER_FUNC_COMMON(ibv_, _symbol, _ret, __VA_ARGS__)

#define LOAD_FUNC_PTR_IBV(_handle, _symbol)                                    \
	LOAD_FUNC_PTR_COMMON(ibv_, _handle, _symbol)

DEFINE_WRAPPER_FUNC_IBV(get_device_list, struct ibv_device **, int *num_devices)
{
	if (UNLIKELY(!FUNC_PTR(get_device_list))) {
		errno = EOPNOTSUPP;
		return NULL;
	}
	return FUNC_PTR(get_device_list)(num_devices);
}

DEFINE_WRAPPER_FUNC_IBV(free_device_list, void, struct ibv_device **list)
{
	if (UNLIKELY(!FUNC_PTR(free_device_list))) {
		errno = EOPNOTSUPP;
		return;
	}
	return FUNC_PTR(free_device_list)(list);
}

DEFINE_WRAPPER_FUNC_IBV(get_device_name, const char *,
			struct ibv_device *device)
{
	if (UNLIKELY(!FUNC_PTR(get_device_name))) {
		errno = EOPNOTSUPP;
		return NULL;
	}
	return FUNC_PTR(get_device_name)(device);
}

static __attribute__((constructor)) void ibverbs_init(void)
{
	void *handle = dlopen("libibverbs.so.1", RTLD_LAZY | RTLD_LOCAL);
	if (UNLIKELY(!handle)) {
		// TODO(fuji): log error msg
		return;
	}
	LOAD_FUNC_PTR_IBV(handle, get_device_list);
	LOAD_FUNC_PTR_IBV(handle, free_device_list);
	LOAD_FUNC_PTR_IBV(handle, get_device_name);
	// do not dlclose the handle in destructor to avoid dereferencing a NULL
	// function pointer during the teardown stage of the process
}
