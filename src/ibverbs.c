#include "infiniband/verbs.h"
#include "utility.h"
#include <dlfcn.h>
#include <stddef.h>

#define DEFINE_WRAPPER_FUNC_IBV(_symbol, _ret, ...)                            \
	DEFINE_WRAPPER_FUNC_COMMON(ibv_, _symbol, _ret, __VA_ARGS__)

#define LOAD_FUNC_PTR_IBV(_handle, _symbol)                                    \
	LOAD_FUNC_PTR_COMMON(ibv_, _handle, _symbol)

DEFINE_WRAPPER_FUNC_IBV(get_device_list, struct ibv_device **, int *num_devices)
{
	RETURN_NOT_EXIST(get_device_list, NULL);
	return FUNC_PTR(get_device_list)(num_devices);
}

DEFINE_WRAPPER_FUNC_IBV(free_device_list, void, struct ibv_device **list)
{
	RETURN_NOT_EXIST(free_device_list);
	return FUNC_PTR(free_device_list)(list);
}

DEFINE_WRAPPER_FUNC_IBV(get_device_name, const char *,
			struct ibv_device *device)
{
	RETURN_NOT_EXIST(get_device_name, NULL);
	return FUNC_PTR(get_device_name)(device);
}

DEFINE_WRAPPER_FUNC_IBV(open_device, struct ibv_context *,
			struct ibv_device *device)
{
	RETURN_NOT_EXIST(open_device, NULL);
	return FUNC_PTR(open_device)(device);
}

DEFINE_WRAPPER_FUNC_IBV(close_device, int, struct ibv_context *context)
{
	RETURN_NOT_EXIST(close_device, -1);
	return FUNC_PTR(close_device)(context);
}

DEFINE_WRAPPER_FUNC_IBV(get_async_event, int, struct ibv_context *context,
			struct ibv_async_event *event)
{
	RETURN_NOT_EXIST(get_async_event, -1);
	return FUNC_PTR(get_async_event)(context, event);
}

DEFINE_WRAPPER_FUNC_IBV(ack_async_event, void, struct ibv_async_event *event)
{
	RETURN_NOT_EXIST(ack_async_event);
	return FUNC_PTR(ack_async_event)(event);
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
	LOAD_FUNC_PTR_IBV(handle, open_device);
	LOAD_FUNC_PTR_IBV(handle, close_device);
	LOAD_FUNC_PTR_IBV(handle, get_async_event);
	LOAD_FUNC_PTR_IBV(handle, ack_async_event);
	// do not dlclose the handle in destructor to avoid dereferencing a NULL
	// function pointer during the teardown stage of the process
}
