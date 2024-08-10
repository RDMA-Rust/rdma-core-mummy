#include "infiniband/driver.h"
#include "infiniband/verbs.h"
#include "utility.h"
#include <dlfcn.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#define DEFINE_WRAPPER_FUNC_IBV(_symbol, _ret, ...)                            \
	DEFINE_WRAPPER_FUNC_COMMON(ibv_, _symbol, _ret, __VA_ARGS__)

#define LOAD_FUNC_PTR_IBV(_handle, _symbol)                                    \
	LOAD_FUNC_PTR_COMMON(ibv_, _handle, _symbol)

DEFINE_WRAPPER_FUNC_IBV(wc_status_str, const char *, enum ibv_wc_status status)
{
	RETURN_NOT_EXIST(wc_status_str, NULL);
	return FUNC_PTR(wc_status_str)(status);
}

DEFINE_WRAPPER_FUNC_IBV(qp_to_qp_ex, struct ibv_qp_ex *, struct ibv_qp *qp)
{
	RETURN_NOT_EXIST(qp_to_qp_ex, NULL);
	return FUNC_PTR(qp_to_qp_ex)(qp);
}

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

DEFINE_WRAPPER_FUNC_IBV(get_device_guid, __be64, struct ibv_device *device)
{
	RETURN_NOT_EXIST(get_device_guid, 0);
	return FUNC_PTR(get_device_guid)(device);
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

DEFINE_WRAPPER_FUNC_IBV(query_device, int, struct ibv_context *context,
			struct ibv_device_attr *device_attr)
{
	RETURN_NOT_EXIST(query_device, EOPNOTSUPP);
	return FUNC_PTR(query_device)(context, device_attr);
}

#undef ibv_query_port
DEFINE_WRAPPER_FUNC_IBV(query_port, int, struct ibv_context *context,
			uint8_t port_num,
			struct _compat_ibv_port_attr *port_attr)
{
	RETURN_NOT_EXIST(query_port, EOPNOTSUPP);
	return FUNC_PTR(query_port)(context, port_num, port_attr);
}

DEFINE_WRAPPER_FUNC_IBV(query_gid, int, struct ibv_context *context,
			uint8_t port_num, int index, union ibv_gid *gid)
{
	RETURN_NOT_EXIST(query_gid, -1);
	return FUNC_PTR(query_gid)(context, port_num, index, gid);
}

DEFINE_WRAPPER_FUNC_IBV(query_pkey, int, struct ibv_context *context,
			uint8_t port_num, int index, __be16 *pkey)
{
	RETURN_NOT_EXIST(query_pkey, -1);
	return FUNC_PTR(query_pkey)(context, port_num, index, pkey);
}

DEFINE_WRAPPER_FUNC_IBV(alloc_pd, struct ibv_pd *, struct ibv_context *context)
{
	RETURN_NOT_EXIST(alloc_pd, NULL);
	return FUNC_PTR(alloc_pd)(context);
}

DEFINE_WRAPPER_FUNC_IBV(dealloc_pd, int, struct ibv_pd *pd)
{
	RETURN_NOT_EXIST(dealloc_pd, EOPNOTSUPP);
	return FUNC_PTR(dealloc_pd)(pd);
}

#undef ibv_reg_mr
DEFINE_WRAPPER_FUNC_IBV(reg_mr, struct ibv_mr *, struct ibv_pd *pd, void *addr,
			size_t length, int access)
{
	RETURN_NOT_EXIST(reg_mr, NULL);
	return FUNC_PTR(reg_mr)(pd, addr, length, access);
}

#undef ibv_reg_mr_iova
DEFINE_WRAPPER_FUNC_IBV(reg_mr_iova, struct ibv_mr *, struct ibv_pd *pd,
			void *addr, size_t length, uint64_t iova, int access)
{
	RETURN_NOT_EXIST(reg_mr_iova, NULL);
	return FUNC_PTR(reg_mr_iova)(pd, addr, length, iova, access);
}

DEFINE_WRAPPER_FUNC_IBV(reg_mr_iova2, struct ibv_mr *, struct ibv_pd *pd,
			void *addr, size_t length, uint64_t iova,
			unsigned int access)
{
	if (LIKELY(FUNC_PTR(reg_mr_iova2))) {
		return FUNC_PTR(reg_mr_iova2)(pd, addr, length, iova, access);
	}
	if ((access & IBV_ACCESS_OPTIONAL_RANGE) != 0) {
		// we are not able to fallback to legacy version if optional
		// access flags are specified
		errno = EOPNOTSUPP;
		return NULL;
	}
	// handle compatibility with old rdma-core
	if ((uintptr_t)addr == iova) {
		return ibv_reg_mr(pd, addr, length, access);
	}
	return ibv_reg_mr_iova(pd, addr, length, iova, access);
}

DEFINE_WRAPPER_FUNC_IBV(dereg_mr, int, struct ibv_mr *mr)
{
	RETURN_NOT_EXIST(dereg_mr, EOPNOTSUPP);
	return FUNC_PTR(dereg_mr)(mr);
}

DEFINE_WRAPPER_FUNC_IBV(create_comp_channel, struct ibv_comp_channel *,
			struct ibv_context *context)
{
	RETURN_NOT_EXIST(create_comp_channel, NULL);
	return FUNC_PTR(create_comp_channel)(context);
}

DEFINE_WRAPPER_FUNC_IBV(destroy_comp_channel, int,
			struct ibv_comp_channel *channel)
{
	RETURN_NOT_EXIST(destroy_comp_channel, EOPNOTSUPP);
	return FUNC_PTR(destroy_comp_channel)(channel);
}

DEFINE_WRAPPER_FUNC_IBV(create_cq, struct ibv_cq *, struct ibv_context *context,
			int cqe, void *cq_context,
			struct ibv_comp_channel *channel, int comp_vector)
{
	RETURN_NOT_EXIST(create_cq, NULL);
	return FUNC_PTR(create_cq)(context, cqe, cq_context, channel,
				   comp_vector);
}

DEFINE_WRAPPER_FUNC_IBV(destroy_cq, int, struct ibv_cq *cq)
{
	RETURN_NOT_EXIST(destroy_cq, EOPNOTSUPP);
	return FUNC_PTR(destroy_cq)(cq);
}

DEFINE_WRAPPER_FUNC_IBV(get_cq_event, int, struct ibv_comp_channel *channel,
			struct ibv_cq **cq, void **cq_context)
{
	RETURN_NOT_EXIST(get_cq_event, -1);
	return FUNC_PTR(get_cq_event)(channel, cq, cq_context);
}

DEFINE_WRAPPER_FUNC_IBV(ack_cq_events, void, struct ibv_cq *cq,
			unsigned int nevents)
{
	RETURN_NOT_EXIST(ack_cq_events);
	return FUNC_PTR(ack_cq_events)(cq, nevents);
}

DEFINE_WRAPPER_FUNC_IBV(create_srq, struct ibv_srq *, struct ibv_pd *pd,
			struct ibv_srq_init_attr *srq_init_attr)
{
	RETURN_NOT_EXIST(create_srq, NULL);
	return FUNC_PTR(create_srq)(pd, srq_init_attr);
}

DEFINE_WRAPPER_FUNC_IBV(destroy_srq, int, struct ibv_srq *srq)
{
	RETURN_NOT_EXIST(destroy_srq, EOPNOTSUPP);
	return FUNC_PTR(destroy_srq)(srq);
}

DEFINE_WRAPPER_FUNC_IBV(create_qp, struct ibv_qp *, struct ibv_pd *pd,
			struct ibv_qp_init_attr *qp_init_attr)
{
	RETURN_NOT_EXIST(create_qp, NULL);
	return FUNC_PTR(create_qp)(pd, qp_init_attr);
}

DEFINE_WRAPPER_FUNC_IBV(modify_qp, int, struct ibv_qp *qp,
			struct ibv_qp_attr *attr, int attr_mask)
{
	RETURN_NOT_EXIST(modify_qp, EOPNOTSUPP);
	return FUNC_PTR(modify_qp)(qp, attr, attr_mask);
}

DEFINE_WRAPPER_FUNC_IBV(query_qp, int, struct ibv_qp *qp,
			struct ibv_qp_attr *attr, int attr_mask,
			struct ibv_qp_init_attr *init_attr)
{
	RETURN_NOT_EXIST(query_qp, EOPNOTSUPP);
	return FUNC_PTR(query_qp)(qp, attr, attr_mask, init_attr);
}

DEFINE_WRAPPER_FUNC_IBV(destroy_qp, int, struct ibv_qp *qp)
{
	RETURN_NOT_EXIST(destroy_qp, EOPNOTSUPP);
	return FUNC_PTR(destroy_qp)(qp);
}

DEFINE_WRAPPER_FUNC_IBV(create_ah, struct ibv_ah *, struct ibv_pd *pd,
			struct ibv_ah_attr *attr)
{
	RETURN_NOT_EXIST(create_ah, NULL);
	return FUNC_PTR(create_ah)(pd, attr);
}

DEFINE_WRAPPER_FUNC_IBV(init_ah_from_wc, int, struct ibv_context *context,
			uint8_t port_num, struct ibv_wc *wc,
			struct ibv_grh *grh, struct ibv_ah_attr *ah_attr)
{
	RETURN_NOT_EXIST(init_ah_from_wc, -1);
	return FUNC_PTR(init_ah_from_wc)(context, port_num, wc, grh, ah_attr);
}

DEFINE_WRAPPER_FUNC_IBV(create_ah_from_wc, struct ibv_ah *, struct ibv_pd *pd,
			struct ibv_wc *wc, struct ibv_grh *grh,
			uint8_t port_num)
{
	RETURN_NOT_EXIST(create_ah_from_wc, NULL);
	return FUNC_PTR(create_ah_from_wc)(pd, wc, grh, port_num);
}

DEFINE_WRAPPER_FUNC_IBV(destroy_ah, int, struct ibv_ah *ah)
{
	RETURN_NOT_EXIST(destroy_ah, EOPNOTSUPP);
	return FUNC_PTR(destroy_ah)(ah);
}

DEFINE_WRAPPER_FUNC_IBV(attach_mcast, int, struct ibv_qp *qp,
			const union ibv_gid *gid, uint16_t lid)
{
	RETURN_NOT_EXIST(attach_mcast, EOPNOTSUPP);
	return FUNC_PTR(attach_mcast)(qp, gid, lid);
}

DEFINE_WRAPPER_FUNC_IBV(detach_mcast, int, struct ibv_qp *qp,
			const union ibv_gid *gid, uint16_t lid)
{
	RETURN_NOT_EXIST(detach_mcast, EOPNOTSUPP);
	return FUNC_PTR(detach_mcast)(qp, gid, lid);
}

DEFINE_WRAPPER_FUNC_IBV(fork_init, int, void)
{
	RETURN_NOT_EXIST(fork_init, EOPNOTSUPP);
	return FUNC_PTR(fork_init)();
}

DEFINE_WRAPPER_FUNC_IBV(event_type_str, const char *, enum ibv_event_type event)
{
	RETURN_NOT_EXIST(event_type_str, NULL);
	return FUNC_PTR(event_type_str)(event);
}

// from driver.h
DEFINE_WRAPPER_FUNC_IBV(get_sysfs_path, const char *, void)
{
	RETURN_NOT_EXIST(get_sysfs_path, NULL);
	return FUNC_PTR(get_sysfs_path)();
}

DEFINE_WRAPPER_FUNC_IBV(read_sysfs_file, int, const char *dir, const char *file,
			char *buf, size_t size)
{
	RETURN_NOT_EXIST(read_sysfs_file, -1);
	return FUNC_PTR(read_sysfs_file)(dir, file, buf, size);
}

DEFINE_WRAPPER_FUNC_IBV(query_gid_type, int, struct ibv_context *context,
			uint8_t port_num, unsigned int index,
			enum ibv_gid_type_sysfs *type)
{
	RETURN_NOT_EXIST(query_gid_type, EOPNOTSUPP);
	return FUNC_PTR(query_gid_type)(context, port_num, index, type);
}

static __attribute__((constructor)) void mummy_ibverbs_init(void)
{
	void *handle = dlopen("libibverbs.so.1", RTLD_LAZY | RTLD_LOCAL);
	if (UNLIKELY(!handle)) {
		// TODO(fuji): log error msg
		return;
	}
	LOAD_FUNC_PTR_IBV(handle, wc_status_str);
	LOAD_FUNC_PTR_IBV(handle, qp_to_qp_ex);
	LOAD_FUNC_PTR_IBV(handle, get_device_list);
	LOAD_FUNC_PTR_IBV(handle, free_device_list);
	LOAD_FUNC_PTR_IBV(handle, get_device_name);
	LOAD_FUNC_PTR_IBV(handle, get_device_guid);
	LOAD_FUNC_PTR_IBV(handle, open_device);
	LOAD_FUNC_PTR_IBV(handle, close_device);
	LOAD_FUNC_PTR_IBV(handle, get_async_event);
	LOAD_FUNC_PTR_IBV(handle, ack_async_event);
	LOAD_FUNC_PTR_IBV(handle, query_device);
	LOAD_FUNC_PTR_IBV(handle, query_port);
	LOAD_FUNC_PTR_IBV(handle, query_gid);
	LOAD_FUNC_PTR_IBV(handle, query_pkey);
	LOAD_FUNC_PTR_IBV(handle, alloc_pd);
	LOAD_FUNC_PTR_IBV(handle, dealloc_pd);
	LOAD_FUNC_PTR_IBV(handle, reg_mr);
	LOAD_FUNC_PTR_IBV(handle, reg_mr_iova);
	LOAD_FUNC_PTR_IBV(handle, reg_mr_iova2);
	LOAD_FUNC_PTR_IBV(handle, dereg_mr);
	LOAD_FUNC_PTR_IBV(handle, create_comp_channel);
	LOAD_FUNC_PTR_IBV(handle, destroy_comp_channel);
	LOAD_FUNC_PTR_IBV(handle, create_cq);
	LOAD_FUNC_PTR_IBV(handle, destroy_cq);
	LOAD_FUNC_PTR_IBV(handle, get_cq_event);
	LOAD_FUNC_PTR_IBV(handle, ack_cq_events);
	LOAD_FUNC_PTR_IBV(handle, create_srq);
	LOAD_FUNC_PTR_IBV(handle, destroy_srq);
	LOAD_FUNC_PTR_IBV(handle, create_qp);
	LOAD_FUNC_PTR_IBV(handle, modify_qp);
	LOAD_FUNC_PTR_IBV(handle, query_qp);
	LOAD_FUNC_PTR_IBV(handle, destroy_qp);
	LOAD_FUNC_PTR_IBV(handle, create_ah);
	LOAD_FUNC_PTR_IBV(handle, init_ah_from_wc);
	LOAD_FUNC_PTR_IBV(handle, create_ah_from_wc);
	LOAD_FUNC_PTR_IBV(handle, destroy_ah);
	LOAD_FUNC_PTR_IBV(handle, attach_mcast);
	LOAD_FUNC_PTR_IBV(handle, detach_mcast);
	LOAD_FUNC_PTR_IBV(handle, fork_init);
	LOAD_FUNC_PTR_IBV(handle, event_type_str);
	// from driver.h
	LOAD_FUNC_PTR_IBV(handle, get_sysfs_path);
	LOAD_FUNC_PTR_IBV(handle, read_sysfs_file);
	LOAD_FUNC_PTR_IBV(handle, query_gid_type);
	// do not dlclose the handle in destructor to avoid dereferencing a NULL
	// function pointer during the teardown stage of the process
}
