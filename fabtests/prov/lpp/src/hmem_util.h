#include "test_util.h"

int hmem_cuda_init(void);
void hmem_cuda_cleanup(void);
int hmem_cuda_alloc(void *uaddr, size_t len);
void hmem_cuda_free(void *uaddr);
int hmem_cuda_memcpy_h2d(void *dst, void *src, size_t len);
int hmem_cuda_memcpy_d2h(void *dst, void *src, size_t len);

int hmem_rocm_init(void);
void hmem_rocm_cleanup(void);
int hmem_rocm_alloc(void *uaddr, size_t len);
void hmem_rocm_free(void *uaddr);
int hmem_rocm_memcpy_h2d(void *dst, const void *src, size_t len);
int hmem_rocm_memcpy_d2h(void *dst, const void *src, size_t len);

