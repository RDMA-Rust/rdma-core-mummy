#include "infiniband/umad.h"
#include "utility.h"
#include <errno.h>

#define DEFINE_WRAPPER_FUNC_UMAD(_symbol, _ret, ...)                           \
	DEFINE_WRAPPER_FUNC_COMMON(umad_, _symbol, _ret, __VA_ARGS__)

#define LOAD_FUNC_PTR_UMAD(_handle, _symbol)                                   \
	LOAD_FUNC_PTR_COMMON(umad_, _handle, _symbol)

DEFINE_WRAPPER_FUNC_UMAD(init, int, void)
{
	RETURN_NOT_EXIST(init, -1);
	return FUNC_PTR(init)();
}

DEFINE_WRAPPER_FUNC_UMAD(done, int, void)
{
	RETURN_NOT_EXIST(done, -1);
	return FUNC_PTR(done)();
}

DEFINE_WRAPPER_FUNC_UMAD(open_port, int, const char *ca_name, int portnum)
{
	RETURN_NOT_EXIST(open_port, -EOPNOTSUPP);
	return FUNC_PTR(open_port)(ca_name, portnum);
}

DEFINE_WRAPPER_FUNC_UMAD(close_port, int, int portid)
{
	RETURN_NOT_EXIST(close_port, -EOPNOTSUPP);
	return FUNC_PTR(close_port)(portid);
}

DEFINE_WRAPPER_FUNC_UMAD(get_mad, void *, void *umad)
{
	RETURN_NOT_EXIST(get_mad, NULL);
	return FUNC_PTR(get_mad)(umad);
}

DEFINE_WRAPPER_FUNC_UMAD(size, size_t, void)
{
	RETURN_NOT_EXIST(size, 0);
	return FUNC_PTR(size)();
}

DEFINE_WRAPPER_FUNC_UMAD(set_pkey, int, void *umad, int pkey_index)
{
	RETURN_NOT_EXIST(set_pkey, -EOPNOTSUPP);
	return FUNC_PTR(set_pkey)(umad, pkey_index);
}

DEFINE_WRAPPER_FUNC_UMAD(send, int, int portid, int agentid, void *umad,
			 int length, int timeout_ms, int retries)
{
	RETURN_NOT_EXIST(send, -EOPNOTSUPP);
	return FUNC_PTR(send)(portid, agentid, umad, length, timeout_ms,
			      retries);
}

DEFINE_WRAPPER_FUNC_UMAD(recv, int, int portid, void *umad, int *length,
			 int timeout_ms)
{
	RETURN_NOT_EXIST(recv, -EOPNOTSUPP);
	return FUNC_PTR(recv)(portid, umad, length, timeout_ms);
}

DEFINE_WRAPPER_FUNC_UMAD(register, int, int portid, int mgmt_class,
			 int mgmt_version, uint8_t rmpp_version,
			 long method_mask[16 / sizeof(long)])
{
	RETURN_NOT_EXIST(register, -EOPNOTSUPP);
	return FUNC_PTR(register)(portid, mgmt_class, mgmt_version,
				  rmpp_version, method_mask);
}

DEFINE_WRAPPER_FUNC_UMAD(unregister, int, int portid, int agentid)
{
	RETURN_NOT_EXIST(unregister, -EOPNOTSUPP);
	return FUNC_PTR(unregister)(portid, agentid);
}

static __attribute__((constructor)) void ibumad_init(void)
{
	void *handle = dlopen("libibumad.so.3", RTLD_LAZY | RTLD_LOCAL);
	if (UNLIKELY(!handle)) {
		// TODO(fuji): log error msg
		return;
	}
	LOAD_FUNC_PTR_UMAD(handle, init);
	LOAD_FUNC_PTR_UMAD(handle, done);
	LOAD_FUNC_PTR_UMAD(handle, open_port);
	LOAD_FUNC_PTR_UMAD(handle, close_port);
	LOAD_FUNC_PTR_UMAD(handle, get_mad);
	LOAD_FUNC_PTR_UMAD(handle, size);
	LOAD_FUNC_PTR_UMAD(handle, set_pkey);
	LOAD_FUNC_PTR_UMAD(handle, send);
	LOAD_FUNC_PTR_UMAD(handle, recv);
	LOAD_FUNC_PTR_UMAD(handle, register);
	LOAD_FUNC_PTR_UMAD(handle, unregister);
}
