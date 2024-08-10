#include "rdma/rdma_cma.h"
#include "rdma/rdma_verbs.h"
#include "utility.h"
#include <stddef.h>

#define DEFINE_WRAPPER_FUNC_RDMA(_symbol, _ret, ...)                           \
	DEFINE_WRAPPER_FUNC_COMMON(rdma_, _symbol, _ret, __VA_ARGS__)

#define LOAD_FUNC_PTR_RDMA(_handle, _symbol)                                   \
	LOAD_FUNC_PTR_COMMON(rdma_, _handle, _symbol)

DEFINE_WRAPPER_FUNC_RDMA(create_event_channel, struct rdma_event_channel *,
			 void)
{
	RETURN_NOT_EXIST(create_event_channel, NULL);
	return FUNC_PTR(create_event_channel)();
}

DEFINE_WRAPPER_FUNC_RDMA(destroy_event_channel, void,
			 struct rdma_event_channel *channel)
{
	RETURN_NOT_EXIST(destroy_event_channel);
	return FUNC_PTR(destroy_event_channel)(channel);
}

DEFINE_WRAPPER_FUNC_RDMA(create_id, int, struct rdma_event_channel *channel,
			 struct rdma_cm_id **id, void *context,
			 enum rdma_port_space ps)
{
	RETURN_NOT_EXIST(create_id, -1);
	return FUNC_PTR(create_id)(channel, id, context, ps);
}

DEFINE_WRAPPER_FUNC_RDMA(destroy_id, int, struct rdma_cm_id *id)
{
	RETURN_NOT_EXIST(destroy_id, -1);
	return FUNC_PTR(destroy_id)(id);
}

DEFINE_WRAPPER_FUNC_RDMA(create_ep, int, struct rdma_cm_id **id,
			 struct rdma_addrinfo *res, struct ibv_pd *pd,
			 struct ibv_qp_init_attr *qp_init_attr)
{
	RETURN_NOT_EXIST(create_ep, -1);
	return FUNC_PTR(create_ep)(id, res, pd, qp_init_attr);
}

DEFINE_WRAPPER_FUNC_RDMA(destroy_ep, void, struct rdma_cm_id *id)
{
	RETURN_NOT_EXIST(destroy_ep);
	return FUNC_PTR(destroy_ep)(id);
}

DEFINE_WRAPPER_FUNC_RDMA(bind_addr, int, struct rdma_cm_id *id,
			 struct sockaddr *addr)
{
	RETURN_NOT_EXIST(bind_addr, -1);
	return FUNC_PTR(bind_addr)(id, addr);
}

DEFINE_WRAPPER_FUNC_RDMA(resolve_addr, int, struct rdma_cm_id *id,
			 struct sockaddr *src_addr, struct sockaddr *dst_addr,
			 int timeout_ms)
{
	RETURN_NOT_EXIST(resolve_addr, -1);
	return FUNC_PTR(resolve_addr)(id, src_addr, dst_addr, timeout_ms);
}

DEFINE_WRAPPER_FUNC_RDMA(resolve_route, int, struct rdma_cm_id *id,
			 int timeout_ms)
{
	RETURN_NOT_EXIST(resolve_route, -1);
	return FUNC_PTR(resolve_route)(id, timeout_ms);
}

DEFINE_WRAPPER_FUNC_RDMA(create_qp, int, struct rdma_cm_id *id,
			 struct ibv_pd *pd,
			 struct ibv_qp_init_attr *qp_init_attr)
{
	RETURN_NOT_EXIST(create_qp, -1);
	return FUNC_PTR(create_qp)(id, pd, qp_init_attr);
}

DEFINE_WRAPPER_FUNC_RDMA(create_qp_ex, int, struct rdma_cm_id *id,
			 struct ibv_qp_init_attr_ex *qp_init_attr)
{
	RETURN_NOT_EXIST(create_qp_ex, -1);
	return FUNC_PTR(create_qp_ex)(id, qp_init_attr);
}

DEFINE_WRAPPER_FUNC_RDMA(destroy_qp, void, struct rdma_cm_id *id)
{
	RETURN_NOT_EXIST(destroy_qp);
	return FUNC_PTR(destroy_qp)(id);
}

DEFINE_WRAPPER_FUNC_RDMA(connect, int, struct rdma_cm_id *id,
			 struct rdma_conn_param *conn_param)
{
	RETURN_NOT_EXIST(connect, -1);
	return FUNC_PTR(connect)(id, conn_param);
}

DEFINE_WRAPPER_FUNC_RDMA(establish, int, struct rdma_cm_id *id)
{
	RETURN_NOT_EXIST(establish, -1);
	return FUNC_PTR(establish)(id);
}

DEFINE_WRAPPER_FUNC_RDMA(listen, int, struct rdma_cm_id *id, int backlog)
{
	RETURN_NOT_EXIST(listen, -1);
	return FUNC_PTR(listen)(id, backlog);
}

DEFINE_WRAPPER_FUNC_RDMA(get_request, int, struct rdma_cm_id *listen,
			 struct rdma_cm_id **id)
{
	RETURN_NOT_EXIST(get_request, -1);
	return FUNC_PTR(get_request)(listen, id);
}

DEFINE_WRAPPER_FUNC_RDMA(accept, int, struct rdma_cm_id *id,
			 struct rdma_conn_param *conn_param)
{
	RETURN_NOT_EXIST(accept, -1);
	return FUNC_PTR(accept)(id, conn_param);
}

DEFINE_WRAPPER_FUNC_RDMA(reject, int, struct rdma_cm_id *id,
			 const void *private_data, uint8_t private_data_len)
{
	RETURN_NOT_EXIST(reject, -1);
	return FUNC_PTR(reject)(id, private_data, private_data_len);
}

DEFINE_WRAPPER_FUNC_RDMA(disconnect, int, struct rdma_cm_id *id)
{
	RETURN_NOT_EXIST(disconnect, -1);
	return FUNC_PTR(disconnect)(id);
}

DEFINE_WRAPPER_FUNC_RDMA(join_multicast, int, struct rdma_cm_id *id,
			 struct sockaddr *addr, void *context)
{
	RETURN_NOT_EXIST(join_multicast, -1);
	return FUNC_PTR(join_multicast)(id, addr, context);
}

DEFINE_WRAPPER_FUNC_RDMA(leave_multicast, int, struct rdma_cm_id *id,
			 struct sockaddr *addr)
{
	RETURN_NOT_EXIST(leave_multicast, -1);
	return FUNC_PTR(leave_multicast)(id, addr);
}

DEFINE_WRAPPER_FUNC_RDMA(join_multicast_ex, int, struct rdma_cm_id *id,
			 struct rdma_cm_join_mc_attr_ex *mc_join_attr,
			 void *context)
{
	RETURN_NOT_EXIST(join_multicast_ex, -1);
	return FUNC_PTR(join_multicast_ex)(id, mc_join_attr, context);
}

DEFINE_WRAPPER_FUNC_RDMA(get_cm_event, int, struct rdma_event_channel *channel,
			 struct rdma_cm_event **event)
{
	RETURN_NOT_EXIST(get_cm_event, -1);
	return FUNC_PTR(get_cm_event)(channel, event);
}

DEFINE_WRAPPER_FUNC_RDMA(ack_cm_event, int, struct rdma_cm_event *event)
{
	RETURN_NOT_EXIST(ack_cm_event, -1);
	return FUNC_PTR(ack_cm_event)(event);
}

DEFINE_WRAPPER_FUNC_RDMA(get_devices, struct ibv_context **, int *num_devices)
{
	RETURN_NOT_EXIST(get_devices, NULL);
	return FUNC_PTR(get_devices)(num_devices);
}

DEFINE_WRAPPER_FUNC_RDMA(free_devices, void, struct ibv_context **list)
{
	RETURN_NOT_EXIST(free_devices);
	return FUNC_PTR(free_devices)(list);
}

DEFINE_WRAPPER_FUNC_RDMA(event_str, const char *, enum rdma_cm_event_type event)
{
	RETURN_NOT_EXIST(event_str, NULL);
	return FUNC_PTR(event_str)(event);
}

DEFINE_WRAPPER_FUNC_RDMA(set_option, int, struct rdma_cm_id *id, int level,
			 int optname, void *optval, size_t optlen)
{
	RETURN_NOT_EXIST(set_option, -1);
	return FUNC_PTR(set_option)(id, level, optname, optval, optlen);
}

DEFINE_WRAPPER_FUNC_RDMA(migrate_id, int, struct rdma_cm_id *id,
			 struct rdma_event_channel *channel)
{
	RETURN_NOT_EXIST(migrate_id, -1);
	return FUNC_PTR(migrate_id)(id, channel);
}

DEFINE_WRAPPER_FUNC_RDMA(getaddrinfo, int, const char *node,
			 const char *service, const struct rdma_addrinfo *hints,
			 struct rdma_addrinfo **res)
{
	RETURN_NOT_EXIST(getaddrinfo, -1);
	return FUNC_PTR(getaddrinfo)(node, service, hints, res);
}

DEFINE_WRAPPER_FUNC_RDMA(freeaddrinfo, void, struct rdma_addrinfo *res)
{
	RETURN_NOT_EXIST(freeaddrinfo);
	return FUNC_PTR(freeaddrinfo)(res);
}

DEFINE_WRAPPER_FUNC_RDMA(init_qp_attr, int, struct rdma_cm_id *id,
			 struct ibv_qp_attr *qp_attr, int *qp_attr_mask)
{
	RETURN_NOT_EXIST(init_qp_attr, -1);
	return FUNC_PTR(init_qp_attr)(id, qp_attr, qp_attr_mask);
}

// from rdma_verbs.h
DEFINE_WRAPPER_FUNC_RDMA(create_srq, int, struct rdma_cm_id *id,
			 struct ibv_pd *pd, struct ibv_srq_init_attr *attr)
{
	RETURN_NOT_EXIST(create_srq, -1);
	return FUNC_PTR(create_srq)(id, pd, attr);
}

static __attribute__((constructor)) void mummy_rdmacm_init(void)
{
	void *handle = dlopen("librdmacm.so.1", RTLD_LAZY | RTLD_LOCAL);
	if (UNLIKELY(!handle)) {
		// TODO(fuji): log error msg
		return;
	}
	LOAD_FUNC_PTR_RDMA(handle, create_event_channel);
	LOAD_FUNC_PTR_RDMA(handle, destroy_event_channel);
	LOAD_FUNC_PTR_RDMA(handle, create_id);
	LOAD_FUNC_PTR_RDMA(handle, destroy_id);
	LOAD_FUNC_PTR_RDMA(handle, create_ep);
	LOAD_FUNC_PTR_RDMA(handle, destroy_ep);
	LOAD_FUNC_PTR_RDMA(handle, bind_addr);
	LOAD_FUNC_PTR_RDMA(handle, resolve_addr);
	LOAD_FUNC_PTR_RDMA(handle, resolve_route);
	LOAD_FUNC_PTR_RDMA(handle, create_qp);
	LOAD_FUNC_PTR_RDMA(handle, create_qp_ex);
	LOAD_FUNC_PTR_RDMA(handle, destroy_qp);
	LOAD_FUNC_PTR_RDMA(handle, connect);
	LOAD_FUNC_PTR_RDMA(handle, establish);
	LOAD_FUNC_PTR_RDMA(handle, listen);
	LOAD_FUNC_PTR_RDMA(handle, get_request);
	LOAD_FUNC_PTR_RDMA(handle, accept);
	LOAD_FUNC_PTR_RDMA(handle, reject);
	LOAD_FUNC_PTR_RDMA(handle, disconnect);
	LOAD_FUNC_PTR_RDMA(handle, join_multicast);
	LOAD_FUNC_PTR_RDMA(handle, leave_multicast);
	LOAD_FUNC_PTR_RDMA(handle, join_multicast_ex);
	LOAD_FUNC_PTR_RDMA(handle, get_cm_event);
	LOAD_FUNC_PTR_RDMA(handle, ack_cm_event);
	LOAD_FUNC_PTR_RDMA(handle, get_devices);
	LOAD_FUNC_PTR_RDMA(handle, free_devices);
	LOAD_FUNC_PTR_RDMA(handle, event_str);
	LOAD_FUNC_PTR_RDMA(handle, set_option);
	LOAD_FUNC_PTR_RDMA(handle, migrate_id);
	LOAD_FUNC_PTR_RDMA(handle, getaddrinfo);
	LOAD_FUNC_PTR_RDMA(handle, freeaddrinfo);
	LOAD_FUNC_PTR_RDMA(handle, init_qp_attr);
	// from rdma_verbs.h
	LOAD_FUNC_PTR_RDMA(handle, create_srq);
}
