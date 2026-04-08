#include "infiniband/mlx5dv.h"
#include "utility.h"
#include <dlfcn.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#define DEFINE_WRAPPER_FUNC_MLX5(_symbol, _ret, ...)                           \
	DEFINE_WRAPPER_FUNC_COMMON(mlx5dv_, _symbol, _ret, __VA_ARGS__)

#define LOAD_FUNC_PTR_MLX5(_handle, _symbol)                                   \
	LOAD_FUNC_PTR_COMMON(mlx5dv_, _handle, _symbol)

DEFINE_WRAPPER_FUNC_MLX5(create_qp, struct ibv_qp *,
			 struct ibv_context *context,
			 struct ibv_qp_init_attr_ex *qp_attr,
			 struct mlx5dv_qp_init_attr *mlx5_qp_attr)
{
	RETURN_NOT_EXIST(create_qp, NULL);
	return FUNC_PTR(create_qp)(context, qp_attr, mlx5_qp_attr);
}

DEFINE_WRAPPER_FUNC_MLX5(query_device, int, struct ibv_context *ctx_in,
			 struct mlx5dv_context *attrs_out)
{
	RETURN_NOT_EXIST(query_device, EOPNOTSUPP);
	return FUNC_PTR(query_device)(ctx_in, attrs_out);
}

DEFINE_WRAPPER_FUNC_MLX5(qp_ex_from_ibv_qp_ex, struct mlx5dv_qp_ex *,
			 struct ibv_qp_ex *qp)
{
	RETURN_NOT_EXIST(qp_ex_from_ibv_qp_ex, NULL);
	return FUNC_PTR(qp_ex_from_ibv_qp_ex)(qp);
}

DEFINE_WRAPPER_FUNC_MLX5(set_context_attr, int, struct ibv_context *context,
			 enum mlx5dv_set_ctx_attr_type type, void *attr)
{
	RETURN_NOT_EXIST(set_context_attr, EOPNOTSUPP);
	return FUNC_PTR(set_context_attr)(context, type, attr);
}

DEFINE_WRAPPER_FUNC_MLX5(query_qp_lag_port, int, struct ibv_qp *qp,
			 uint8_t *port_num, uint8_t *active_port_num)
{
	RETURN_NOT_EXIST(query_qp_lag_port, EOPNOTSUPP);
	return FUNC_PTR(query_qp_lag_port)(qp, port_num, active_port_num);
}

DEFINE_WRAPPER_FUNC_MLX5(modify_qp_lag_port, int, struct ibv_qp *qp,
			 uint8_t port_num)
{
	RETURN_NOT_EXIST(modify_qp_lag_port, EOPNOTSUPP);
	return FUNC_PTR(modify_qp_lag_port)(qp, port_num);
}

DEFINE_WRAPPER_FUNC_MLX5(modify_qp_udp_sport, int, struct ibv_qp *qp,
			 uint16_t udp_sport)
{
	RETURN_NOT_EXIST(modify_qp_udp_sport, EOPNOTSUPP);
	return FUNC_PTR(modify_qp_udp_sport)(qp, udp_sport);
}

DEFINE_WRAPPER_FUNC_MLX5(get_clock_info, int, struct ibv_context *context,
			 struct mlx5dv_clock_info *clock_info)
{
	RETURN_NOT_EXIST(get_clock_info, EOPNOTSUPP);
	return FUNC_PTR(get_clock_info)(context, clock_info);
}

static __attribute__((constructor)) void mlx5_init(void)
{
	void *handle = dlopen("libmlx5.so.1", RTLD_LAZY | RTLD_LOCAL);
	if (UNLIKELY(!handle)) {
		return;
	}
	LOAD_FUNC_PTR_MLX5(handle, create_qp);
	LOAD_FUNC_PTR_MLX5(handle, query_device);
	LOAD_FUNC_PTR_MLX5(handle, qp_ex_from_ibv_qp_ex);
	LOAD_FUNC_PTR_MLX5(handle, set_context_attr);
	LOAD_FUNC_PTR_MLX5(handle, query_qp_lag_port);
	LOAD_FUNC_PTR_MLX5(handle, modify_qp_lag_port);
	LOAD_FUNC_PTR_MLX5(handle, modify_qp_udp_sport);
	LOAD_FUNC_PTR_MLX5(handle, get_clock_info);
	// do not dlclose the handle in destructor to avoid dereferencing a NULL
	// function pointer during the teardown stage of the process
}
