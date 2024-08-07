/*
 * Copyright (c) 2018-2024 GigaIO, Inc. All Rights Reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <pthread.h>
#include <stdio.h>
#include <rdma/fabric.h>
#include <rdma/fi_errno.h>
#include <ofi_enosys.h>
#include <lpp.h>

//
// Common
//
int lpp_fi_no_bind(struct fid *fid, struct fid *bfid, uint64_t flags)
{
	FI_WARN(&lpp_prov, FI_LOG_FABRIC, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_ops_open(struct fid *fid, const char *name, uint64_t flags, void **ops, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_FABRIC, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// AV functions.
//
int lpp_fi_no_av_insertsvc(struct fid_av *av, const char *node, const char *service, fi_addr_t *fi_addr, uint64_t flags, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_AV, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_av_insertsym(struct fid_av *av, const char *node, size_t nodecnt, const char *service, size_t svccnt, fi_addr_t *fi_addr, uint64_t flags, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_AV, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_av_remove(struct fid_av *av, fi_addr_t *fi_addr, size_t count, uint64_t flags)
{
	FI_WARN(&lpp_prov, FI_LOG_AV, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// CM
//
int lpp_fi_no_connect(struct fid_ep *ep, const void *addr, const void *param, size_t paramlen)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_listen(struct fid_pep *pep)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_accept(struct fid_ep *ep, const void *param, size_t paramlen)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_reject(struct fid_pep *pep, fid_t handle, const void *param, size_t paramlen)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_shutdown(struct fid_ep *ep, uint64_t flags)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_setname(fid_t fid, void *addr, size_t addrlen)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_getpeer(struct fid_ep *ep, void *addr, size_t *addrlen)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_join(struct fid_ep *ep, const void *addr, uint64_t flags, struct fid_mc **mc, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// CNTR
//
int lpp_fi_no_cntr_add(struct fid_cntr *cntr, uint64_t value)
{
	FI_WARN(&lpp_prov, FI_LOG_CNTR, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_cntr_adderr(struct fid_cntr *cntr, uint64_t value)
{
	FI_WARN(&lpp_prov, FI_LOG_CNTR, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}
int lpp_fi_no_cntr_set(struct fid_cntr *cntr, uint64_t value)
{
	FI_WARN(&lpp_prov, FI_LOG_CNTR, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_cntr_seterr(struct fid_cntr *cntr, uint64_t value)
{
	FI_WARN(&lpp_prov, FI_LOG_CNTR, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// CQ
//
ssize_t lpp_fi_no_cq_readfrom(struct fid_cq *cq, void *buf, size_t count, fi_addr_t *src_addr)
{
	FI_WARN(&lpp_prov, FI_LOG_CQ, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_cq_sread(struct fid_cq *cq, void *buf, size_t count, const void *cond, int timeout)
{
	FI_WARN(&lpp_prov, FI_LOG_CQ, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_cq_sreadfrom(struct fid_cq *cq, void *buf, size_t count, fi_addr_t *src_addr, const void *cond, int timeout)
{
	FI_WARN(&lpp_prov, FI_LOG_CQ, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_cq_signal(struct fid_cq *cq)
{
	FI_WARN(&lpp_prov, FI_LOG_CQ, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

const char * lpp_fi_no_cq_strerror(struct fid_cq *cq, int prov_errno, const void *err_data, char *buf, size_t len)
{
	FI_WARN(&lpp_prov, FI_LOG_CQ, "%s, Not implemented.\n", __func__);
	return NULL;
}

//
// ENDPOINT
//
int lpp_fi_no_scalable_ep(struct fid_domain *domain, struct fi_info *info, struct fid_ep **sep, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_passive_ep(struct fid_fabric *fabric, struct fi_info *info, struct fid_pep **pep, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_tx_ctx(struct fid_ep *sep, int index, struct fi_tx_attr *attr, struct fid_ep **tx_ep, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_rx_ctx(struct fid_ep *sep, int index, struct fi_rx_attr *attr, struct fid_ep **rx_ep, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_srx_context(struct fid_domain *domain, struct fi_rx_attr *attr, struct fid_ep **rx_ep, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_scalable_ep_bind(struct fid_ep *sep, struct fid *fid, uint64_t flags)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_pep_bind(struct fid_pep *pep, struct fid *fid, uint64_t flags)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_cancel(fid_t fid, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_ep_alias(struct fid_ep *ep, struct fid_ep **alias_ep, uint64_t flags)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_control(struct fid *fid, int command, void *arg)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_getopt(fid_t fid, int level, int optname, void *optval, size_t *optlen)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_setopt(fid_t fid, int level, int optname, const void *optval, size_t optlen)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_rx_size_left(struct fid_ep *ep)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_tx_size_left(struct fid_ep *ep)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_CTRL, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// EQ
//
ssize_t lpp_fi_no_eq_write(struct fid_eq *eq, uint32_t event, const void *buf, size_t len, uint64_t flags)
{
	FI_WARN(&lpp_prov, FI_LOG_EQ, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// MSG
//
ssize_t lpp_fi_no_msg_recvv(struct fid_ep *ep, const struct iovec *iov, void **desc, size_t count, fi_addr_t src_addr, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_msg_senddata(struct fid_ep *ep, const void *buf, size_t len, void *desc, uint64_t data, fi_addr_t dest_addr, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_msg_injectdata(struct fid_ep *ep, const void *buf, size_t len, uint64_t data, fi_addr_t dest_addr)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// RMA
//
ssize_t lpp_fi_no_rma_readv(struct fid_ep *ep, const struct iovec *iov, void **desc, size_t count, fi_addr_t src_addr, uint64_t addr, uint64_t key,
		void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_rma_writev(struct fid_ep *ep, const struct iovec *iov, void **desc, size_t count, fi_addr_t dest_addr, uint64_t addr, uint64_t key,
		void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_rma_writedata(struct fid_ep *ep, const void *buf, size_t len, void *desc, uint64_t data, fi_addr_t dest_addr, uint64_t addr, uint64_t key,
		void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_rma_injectdata(struct fid_ep *ep, const void *buf, size_t len, uint64_t data, fi_addr_t dest_addr, uint64_t addr, uint64_t key)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// TAGGED
//
ssize_t lpp_fi_no_tagged_recvv(struct fid_ep *ep, const struct iovec *iov, void **desc, size_t count, fi_addr_t src_addr, uint64_t tag, uint64_t ignore,
		void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_tagged_sendv(struct fid_ep *ep, const struct iovec *iov, void **desc, size_t count, fi_addr_t dest_addr, uint64_t tag, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

ssize_t lpp_fi_no_tagged_search(struct fid_ep *ep, uint64_t *tag, uint64_t ignore, uint64_t flags, fi_addr_t *src_addr, size_t *len, void *context)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

//
// DOMAIN
//

//
// FABRIC
//

//
// POLL
//
int lpp_fi_no_poll_open(struct fid_domain *domain, struct fi_poll_attr *attr, struct fid_poll **pollset)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_wait_open(struct fid_fabric *fabric, struct fi_wait_attr *attr, struct fid_wait **waitset)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}

int lpp_fi_no_trywait(struct fid_fabric *fabric, struct fid **fids, int count)
{
	FI_WARN(&lpp_prov, FI_LOG_EP_DATA, "%s, Not implemented.\n", __func__);
	return -FI_ENOSYS;
}
