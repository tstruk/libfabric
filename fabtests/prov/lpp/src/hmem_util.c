#include "hmem_util.h"

void hmem_init(void)
{
#ifdef USE_CUDA
	hmem_cuda_init();
#endif
#ifdef USE_ROCM
	hmem_rocm_init();
#endif
}

void hmem_cleanup(void)
{
#ifdef USE_CUDA
	hmem_cuda_cleanup();
#endif
#ifdef USE_ROCM
	hmem_rocm_cleanup();
#endif
}

int hmem_memcpy_d2h(enum fi_hmem_iface iface, void* dst, void* src, size_t len)
{
	switch (iface) {
	case FI_HMEM_CUDA:
		return hmem_cuda_memcpy_d2h(dst, src, len);
		break;
	case FI_HMEM_ROCR:
		return hmem_rocm_memcpy_d2h(dst, src, len);
		break;
	default:
		error("Unsupported hmem iface requested: %d", iface);
		return -EOPNOTSUPP;
		break;
	}

	return 0;
}

int hmem_memcpy_h2d(enum fi_hmem_iface iface, void* dst, void* src, size_t len)
{
	switch (iface) {
	case FI_HMEM_CUDA:
		return hmem_cuda_memcpy_h2d(dst, src, len);
		break;
	case FI_HMEM_ROCR:
		return hmem_rocm_memcpy_h2d(dst, src, len);
		break;
	default:
		error("Unsupported hmem iface requested: %d", iface);
		return -EOPNOTSUPP;
		break;
	}

	return 0;
}

int hmem_alloc(enum fi_hmem_iface iface, void *uaddr, size_t len)
{
	switch (iface) {
	case  FI_HMEM_CUDA:
		return hmem_cuda_alloc(uaddr, len);
		break;
	case  FI_HMEM_ROCR:
		return hmem_rocm_alloc(uaddr, len);
		break;
	default:
		error("hmem iface %d not supported", iface);
		return -ENOSYS;
		break;
	}
}

void hmem_free(enum fi_hmem_iface iface, void *uaddr)
{
	switch (iface) {
	case FI_HMEM_CUDA:
		hmem_cuda_free(uaddr);
		break;
	case FI_HMEM_ROCR:
		hmem_rocm_free(uaddr);
		break;
	default:
		error("Unsupported hmem iface requested: %d", iface);
		break;
	}
}
