/* SPDX-License-Identifier: BSD-2-Clause OR GPL-2.0-only */
/* SPDX-FileCopyrightText: Copyright Amazon.com, Inc. or its affiliates. All rights reserved. */

#include "efa.h"
#include "efa_hmem.h"
#include "rdm/efa_rdm_pkt_type.h"

#if HAVE_CUDA || HAVE_NEURON
static size_t efa_max_eager_msg_size_with_largest_header(struct efa_domain *efa_domain) {
	int mtu_size;

	mtu_size = efa_domain->device->rdm_info->ep_attr->max_msg_size;

	return mtu_size - efa_rdm_pkt_type_get_max_hdr_size();
}
#else
static size_t efa_max_eager_msg_size_with_largest_header(struct efa_domain *efa_domain) {
	return 0;
}
#endif

/**
 * @brief  Initialize the various protocol thresholds tracked in efa_hmem_info
 *         according to the given FI_HMEM interface.
 *
 * @param[in,out]  efa_domain  Pointer to struct efa_domain
 * @param[in]      iface       The FI_HMEM interface to initialize
 *
 * @return  0
 */
static int efa_domain_hmem_info_init_protocol_thresholds(struct efa_domain *efa_domain, enum fi_hmem_iface iface)
{
	struct efa_hmem_info *info = &efa_domain->hmem_info[iface];
	size_t tmp_value;

	/* Fall back to FI_HMEM_SYSTEM initialization logic when p2p is
	 * unavailable */
	if (ofi_hmem_p2p_disabled() || !info->p2p_supported_by_device)
		iface = FI_HMEM_SYSTEM;

	switch (iface) {
	case FI_HMEM_SYSTEM:
		/* We have not yet tested runting with system memory */
		info->runt_size = 0;
		info->max_medium_msg_size = EFA_DEFAULT_INTER_MAX_MEDIUM_MESSAGE_SIZE;
		info->min_read_msg_size = EFA_DEFAULT_INTER_MIN_READ_MESSAGE_SIZE;
		info->min_read_write_size = EFA_DEFAULT_INTER_MIN_READ_WRITE_SIZE;
		fi_param_get_size_t(&efa_prov, "runt_size", &info->runt_size);
		fi_param_get_size_t(&efa_prov, "inter_max_medium_message_size", &info->max_medium_msg_size);
		fi_param_get_size_t(&efa_prov, "inter_min_read_message_size", &info->min_read_msg_size);
		fi_param_get_size_t(&efa_prov, "inter_min_read_write_size", &info->min_read_write_size);
		break;
	case FI_HMEM_CUDA:
		info->runt_size = EFA_DEFAULT_RUNT_SIZE;
		info->max_medium_msg_size = 0;
		info->min_read_msg_size = efa_max_eager_msg_size_with_largest_header(efa_domain) + 1;
		info->min_read_write_size = efa_max_eager_msg_size_with_largest_header(efa_domain) + 1;
		fi_param_get_size_t(&efa_prov, "runt_size", &info->runt_size);
		fi_param_get_size_t(&efa_prov, "inter_min_read_message_size", &info->min_read_msg_size);
		fi_param_get_size_t(&efa_prov, "inter_min_read_write_size", &info->min_read_write_size);
		if (-FI_ENODATA != fi_param_get(&efa_prov, "inter_max_medium_message_size", &tmp_value)) {
			EFA_WARN(FI_LOG_DOMAIN,
			         "The environment variable FI_EFA_INTER_MAX_MEDIUM_MESSAGE_SIZE was set, "
			         "but EFA HMEM via Cuda API only supports eager and runting read protocols. "
			         "The variable will not modify CUDA memory run config.\n");
		}
		break;
	case FI_HMEM_NEURON:
		info->runt_size = EFA_NEURON_RUNT_SIZE;
		info->max_medium_msg_size = 0;
		info->min_read_msg_size = efa_max_eager_msg_size_with_largest_header(efa_domain) + 1;
		info->min_read_write_size = efa_max_eager_msg_size_with_largest_header(efa_domain) + 1;
		fi_param_get_size_t(&efa_prov, "runt_size", &info->runt_size);
		fi_param_get_size_t(&efa_prov, "inter_min_read_message_size", &info->min_read_msg_size);
		fi_param_get_size_t(&efa_prov, "inter_min_read_write_size", &info->min_read_write_size);
		if (-FI_ENODATA != fi_param_get(&efa_prov, "inter_max_medium_message_size", &tmp_value)) {
			EFA_WARN(FI_LOG_DOMAIN,
			         "The environment variable FI_EFA_INTER_MAX_MEDIUM_MESSAGE_SIZE was set, "
			         "but EFA HMEM via Neuron API only supports eager and runting read protocols. "
			         "The variable will not modify CUDA memory run config.\n");
		}
		break;
	case FI_HMEM_SYNAPSEAI:
		info->runt_size = 0;
		info->max_medium_msg_size = 0;
		info->min_read_msg_size = 1;
		info->min_read_write_size = 1;
		if (-FI_ENODATA != fi_param_get_size_t(&efa_prov, "inter_max_medium_message_size", &tmp_value) ||
		    -FI_ENODATA != fi_param_get_size_t(&efa_prov, "inter_min_read_message_size", &tmp_value) ||
		    -FI_ENODATA != fi_param_get_size_t(&efa_prov, "inter_min_read_write_size", &tmp_value) ||
		    -FI_ENODATA != fi_param_get_size_t(&efa_prov, "runt_size", &tmp_value)) {
			EFA_WARN(FI_LOG_DOMAIN,
			        "One or more of the following environment variable(s) were set: ["
			        "FI_EFA_INTER_MAX_MEDIUM_MESSAGE_SIZE, "
			        "FI_EFA_INTER_MIN_READ_MESSAGE_SIZE, "
			        "FI_EFA_INTER_MIN_READ_WRITE_SIZE, "
			        "FI_EFA_RUNT_SIZE"
			        "], but EFA HMEM via Synapse only supports long read protocol. "
			        "The variable(s) will not modify Synapse memory run config.\n");
		}
		break;
	default:
		break;
	}
	return 0;
}

static inline void efa_domain_hmem_info_check_p2p_support_cuda(struct efa_hmem_info *info) {
#if HAVE_CUDA
	cudaError_t cuda_ret;
	void *ptr = NULL;
	struct ibv_mr *ibv_mr;
	int ibv_access = IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_READ;
	size_t len = ofi_get_page_size() * 2;
	int ret;
	int dmabuf_fd;
	uint64_t dmabuf_offset;

	cuda_ret = ofi_cudaMalloc(&ptr, len);
	if (cuda_ret != cudaSuccess) {
		info->initialized = false;
		EFA_WARN(FI_LOG_DOMAIN, "Failed to allocate CUDA buffer: %s\n",
			 ofi_cudaGetErrorString(cuda_ret));
		return;
	}
#if HAVE_EFA_DMABUF_MR
	ret = cuda_get_dmabuf_fd(ptr, len, &dmabuf_fd, &dmabuf_offset);
	if (ret == FI_SUCCESS) {
		ibv_mr = ibv_reg_dmabuf_mr(g_device_list[0].ibv_pd, dmabuf_offset,
					   len, (uint64_t)ptr, dmabuf_fd, ibv_access);
		if (!ibv_mr) {
			EFA_INFO(FI_LOG_DOMAIN,
				"Unable to register CUDA device buffer via dmabuf: %s. "
				"Fall back to ibv_reg_mr\n", fi_strerror(-errno));
			ibv_mr = ibv_reg_mr(g_device_list[0].ibv_pd, ptr, len, ibv_access);
		}
	} else {
		EFA_INFO(FI_LOG_DOMAIN,
			"Unable to retrieve dmabuf fd of CUDA device buffer: %d. "
			"Fall back to ibv_reg_mr\n", ret);
		ibv_mr = ibv_reg_mr(g_device_list[0].ibv_pd, ptr, len, ibv_access);
	}
#else
	ibv_mr = ibv_reg_mr(g_device_list[0].ibv_pd, ptr, len, ibv_access);
#endif

	if (!ibv_mr) {
		info->p2p_supported_by_device = false;
		EFA_WARN(FI_LOG_DOMAIN,
			 "Failed to register CUDA buffer with the EFA device, FI_HMEM transfers that require peer to peer support will fail.\n");
		ofi_cudaFree(ptr);
		return;
	}

	ret = ibv_dereg_mr(ibv_mr);
	ofi_cudaFree(ptr);
	if (ret) {
		EFA_WARN(FI_LOG_DOMAIN,
			 "Failed to deregister CUDA buffer: %s\n",
			 fi_strerror(-ret));
		return;
	}

	info->p2p_supported_by_device = true;
	return;

#endif
	return;
}

static inline void efa_domain_hmem_info_check_p2p_support_neuron(struct efa_hmem_info *info) {
#if HAVE_NEURON
	struct ibv_mr *ibv_mr = NULL;
	int ibv_access = IBV_ACCESS_LOCAL_WRITE;
	void *handle;
	void *ptr = NULL;
	size_t len = ofi_get_page_size() * 2;
	int dmabuf_fd;
	uint64_t offset;
	int ret;

	if (g_device_list[0].device_caps & EFADV_DEVICE_ATTR_CAPS_RDMA_READ) {
		ibv_access |= IBV_ACCESS_REMOTE_READ;
	}

	ptr = neuron_alloc(&handle, len);
	/*
	 * neuron_alloc will fail if application did not call nrt_init,
	 * which is ok if it's not running neuron workloads. libfabric
	 * will move on and leave info->initialized as false.
	 */
	if (!ptr) {
		info->initialized = false;
		EFA_INFO(FI_LOG_DOMAIN, "Cannot allocate Neuron buffer\n");
		return;
	}

#if HAVE_EFA_DMABUF_MR
	ret = neuron_get_dmabuf_fd(ptr, (uint64_t)len, &dmabuf_fd, &offset);
	if (ret == FI_SUCCESS) {
		ibv_mr = ibv_reg_dmabuf_mr(
					g_device_list[0].ibv_pd, offset,
					len, (uint64_t)ptr, dmabuf_fd, ibv_access);
	} else if (ret == -FI_EOPNOTSUPP) {
		EFA_INFO(FI_LOG_MR,
			"Unable to retrieve dmabuf fd of Neuron device buffer, "
			"Fall back to ibv_reg_mr\n");
		ibv_mr = ibv_reg_mr(g_device_list[0].ibv_pd, ptr, len, ibv_access);
	}
#else
	ibv_mr = ibv_reg_mr(g_device_list[0].ibv_pd, ptr, len, ibv_access);
#endif

	if (!ibv_mr) {
		info->p2p_supported_by_device = false;
		/* We do not expect to support Neuron on non p2p systems */
		EFA_WARN(FI_LOG_DOMAIN,
		         "Failed to register Neuron buffer with the EFA device, "
		         "FI_HMEM transfers that require peer to peer support will fail.\n");
		neuron_free(&handle);
		return;
	}

	ret = ibv_dereg_mr(ibv_mr);
	neuron_free(&handle);
	if (ret) {
		EFA_WARN(FI_LOG_DOMAIN,
			 "Failed to deregister Neuron buffer: %s\n",
			 fi_strerror(-ret));
		return;
	}

	info->p2p_supported_by_device = true;
	return;
#endif
	return;
}

/**
 * @brief Initialize the efa_hmem_info state for iface
 *
 * @param[in,out]  efa_domain  Pointer to struct efa_domain
 * @param[in]      iface       HMEM interface
 */
static void
efa_domain_hmem_info_init_iface(struct efa_domain *efa_domain, enum fi_hmem_iface iface)
{
	struct efa_hmem_info *info = &efa_domain->hmem_info[iface];

	if (!ofi_hmem_is_initialized(iface)) {
		EFA_INFO(FI_LOG_DOMAIN, "%s is not initialized\n",
		         fi_tostr(&iface, FI_TYPE_HMEM_IFACE));
		return;
	}

	if ((iface == FI_HMEM_SYNAPSEAI || iface == FI_HMEM_NEURON) &&
	    !efa_device_support_rdma_read()) {
		EFA_WARN(FI_LOG_DOMAIN,
			 "No EFA RDMA read support, transfers using %s will fail.\n",
			 fi_tostr(&iface, FI_TYPE_HMEM_IFACE));
		return;
	}

	info->initialized = true;
	info->p2p_disabled_by_user = (iface == FI_HMEM_SYSTEM) ? false : ofi_hmem_p2p_disabled();

	if (iface == FI_HMEM_SYNAPSEAI || iface == FI_HMEM_SYSTEM) {
		info->p2p_supported_by_device = true;
	} else if (info->p2p_disabled_by_user) {
		info->p2p_supported_by_device = false;
	} else {
		if (iface == FI_HMEM_CUDA)
			efa_domain_hmem_info_check_p2p_support_cuda(info);
		if (iface == FI_HMEM_NEURON)
			efa_domain_hmem_info_check_p2p_support_neuron(info);
		if (!info->p2p_supported_by_device)
			EFA_INFO(FI_LOG_DOMAIN, "%s P2P support is not available.\n", fi_tostr(&iface, FI_TYPE_HMEM_IFACE));
	}

	info->p2p_required_by_impl = true;
	/* If user is using libfabric API 1.18 or later, by default EFA
	* provider is permitted to use CUDA library to support CUDA
	* memory, therefore p2p is not required.
	*/
	if (iface == FI_HMEM_CUDA &&
	    FI_VERSION_GE(efa_domain->util_domain.fabric->fabric_fid.api_version, FI_VERSION(1, 18)))
		info->p2p_required_by_impl = !hmem_ops[iface].initialized;
	if (iface == FI_HMEM_SYSTEM)
		info->p2p_required_by_impl = false;

	efa_domain_hmem_info_init_protocol_thresholds(efa_domain, iface);
}

/**
 * @brief   Validate an FI_OPT_FI_HMEM_P2P (FI_OPT_ENDPOINT) option for a
 *          specified HMEM interface.
 *          Also update hmem_info[iface]->p2p_disabled_by_user accordingly.
 *
 * @param[in,out]  domain   The efa_domain struct which contains an efa_hmem_info array
 * @param[in]      iface    The fi_hmem_iface enum of the FI_HMEM interface to validate
 * @param[in]      p2p_opt  The P2P option to validate
 *
 * @return  0 if the P2P option is valid for the given interface
 *         -FI_OPNOTSUPP if the P2P option is invalid
 *         -FI_ENODATA if the given HMEM interface was not initialized
 *         -FI_EINVAL if p2p_opt is not a valid FI_OPT_FI_HMEM_P2P option
 */
int efa_domain_hmem_validate_p2p_opt(struct efa_domain *efa_domain, enum fi_hmem_iface iface, int p2p_opt)
{
	struct efa_hmem_info *info = &efa_domain->hmem_info[iface];

	if (OFI_UNLIKELY(!info->initialized))
		return -FI_ENODATA;

	switch (p2p_opt) {
	case FI_HMEM_P2P_REQUIRED:
		if (OFI_UNLIKELY(ofi_hmem_p2p_disabled()) || !info->p2p_supported_by_device)
			return -FI_EOPNOTSUPP;

		info->p2p_disabled_by_user = false;
		return 0;
	/*
	 * According to fi_setopt() document:
	 *
	 *     ENABLED means a provider may use P2P.
	 *     PREFERED means a provider should prefer P2P if it is available.
	 *
	 * These options does not require that p2p is supported by device,
	 * nor do they prohibit that p2p is required by implementation. 
	 * Therefore they are always supported unless p2p is disabled.
	 */
	case FI_HMEM_P2P_PREFERRED:
	case FI_HMEM_P2P_ENABLED:
		if (OFI_UNLIKELY(ofi_hmem_p2p_disabled()))
			return -FI_EOPNOTSUPP;

		info->p2p_disabled_by_user = false;
		return 0;

	case FI_HMEM_P2P_DISABLED:
		if (info->p2p_required_by_impl)
			return -FI_EOPNOTSUPP;

		info->p2p_disabled_by_user = true;
		return 0;
	}

	return -FI_EINVAL;
}

/**
 * @brief Initialize the hmem_info structs for
 * all of the HMEM devices. The device hmem_info
 * struct will be used to determine which efa transfer
 * protocol should be selected.
 *
 * @param[in,out]  efa_domain  Pointer to struct efa_domain to be initialized
 *
 * @return  0 on success
 *          negative libfabric error code on an unexpected error
 */
int efa_domain_hmem_info_init_all(struct efa_domain *efa_domain)
{
	int ret = 0, i = 0;

	if(g_device_cnt <= 0) {
		return -FI_ENODEV;
	}

	memset(efa_domain->hmem_info, 0, OFI_HMEM_MAX * sizeof(struct efa_hmem_info));

	EFA_HMEM_IFACE_FOREACH(i) {
		efa_domain_hmem_info_init_iface(efa_domain, efa_hmem_ifaces[i]);
	}

	return ret;
}

/**
 * @brief Copy data from a hmem IOV to a system buffer
 *
 * @param[in]   desc          Array of memory desc corresponding to IOV buffers
 * @param[out]  buff          Target buffer (system memory)
 * @param[in]   buff_size     The size of the target buffer
 * @param[in]   hmem_iov      IOV data source
 * @param[in]   iov_count     Number of IOV structures in IOV array
 * @return  number of bytes copied on success, or a negative error code
 */
ssize_t efa_copy_from_hmem_iov(void **desc, char *buff, size_t buff_size,
                               const struct iovec *hmem_iov, size_t iov_count)
{
	int ret = -1;
	size_t i, data_size = 0;

	for (i = 0; i < iov_count; i++) {
		if (data_size + hmem_iov[i].iov_len > buff_size) {
			EFA_WARN(FI_LOG_CQ, "IOV is larger than the target buffer\n");
			return -FI_ETRUNC;
		}

		ret = efa_copy_from_hmem(desc[i], buff + data_size,
		                         hmem_iov[i].iov_base, hmem_iov[i].iov_len);

		if (ret < 0)
			return ret;

		data_size += hmem_iov[i].iov_len;
	}

	return data_size;
}

/**
 * @brief Copy data from a system buffer to a hmem IOV
 *
 * @param[in]    desc            Array of memory desc corresponding to IOV buffers
 * @param[out]   hmem_iov        Target IOV (HMEM)
 * @param[in]    iov_count       Number of IOV entries in vector
 * @param[in]    buff            System buffer data source
 * @param[in]    buff_size       Size of data to copy
 * @return  number of bytes copied on success, or a negative error code
 */
ssize_t efa_copy_to_hmem_iov(void **desc, struct iovec *hmem_iov,
                             size_t iov_count, char *buff, size_t buff_size)
{
	int ret;
	size_t i, bytes_remaining = buff_size, size;

	for (i = 0; i < iov_count && bytes_remaining; i++) {
		size = hmem_iov[i].iov_len;
		if (bytes_remaining < size) {
			size = bytes_remaining;
		}

		ret = efa_copy_to_hmem(desc[i], hmem_iov[i].iov_base, buff, size);

		if (ret < 0)
			return ret;

		bytes_remaining -= size;
	}

	if (bytes_remaining) {
		EFA_WARN(FI_LOG_CQ, "Source buffer is larger than target IOV\n");
		return -FI_ETRUNC;
	}
	return buff_size;
}
