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

#ifndef	_LPP_ENOSYS_H_
#define	_LPP_ENOSYS_H_

//
// Common
//
int lpp_fi_no_bind(struct fid *, struct fid *, uint64_t);
int lpp_fi_no_ops_open(struct fid *, const char *, uint64_t, void **, void *);

//
// AV
//
int lpp_fi_no_av_insertsvc(struct fid_av *, const char *, const char *, fi_addr_t *, uint64_t, void *);
int lpp_fi_no_av_insertsym(struct fid_av *, const char *, size_t, const char *, size_t, fi_addr_t *, uint64_t, void *);
int lpp_fi_no_av_remove(struct fid_av *, fi_addr_t *fi_addr, size_t, uint64_t);

//
// CM
//
int lpp_fi_no_connect(struct fid_ep *, const void *, const void *, size_t paramlen);
int lpp_fi_no_listen(struct fid_pep *);
int lpp_fi_no_accept(struct fid_ep *, const void *, size_t paramlen);
int lpp_fi_no_reject(struct fid_pep *, fid_t, const void *, size_t paramlen);
int lpp_fi_no_shutdown(struct fid_ep *, uint64_t);
int lpp_fi_no_setname(fid_t, void *, size_t addrlen);
int lpp_fi_no_getpeer(struct fid_ep *, void *, size_t *);
int lpp_fi_no_join(struct fid_ep *, const void *, uint64_t, struct fid_mc **, void *);

//
// CNTR
//
int lpp_fi_no_cntr_add(struct fid_cntr *, uint64_t);
int lpp_fi_no_cntr_adderr(struct fid_cntr *, uint64_t);
int lpp_fi_no_cntr_set(struct fid_cntr *, uint64_t);
int lpp_fi_no_cntr_seterr(struct fid_cntr *, uint64_t);

//
// CQ
//
ssize_t lpp_fi_no_cq_readfrom(struct fid_cq *, void *, size_t, fi_addr_t *);
ssize_t lpp_fi_no_cq_sread(struct fid_cq *, void *, size_t, const void *, int);
ssize_t lpp_fi_no_cq_sreadfrom(struct fid_cq *, void *, size_t, fi_addr_t *, const void *, int);
int lpp_fi_no_cq_signal(struct fid_cq *);
const char * lpp_fi_no_cq_strerror(struct fid_cq *, int, const void *, char *, size_t);

//
// ENDPOINT
//
int lpp_fi_no_scalable_ep(struct fid_domain *, struct fi_info *, struct fid_ep **, void *);
int lpp_fi_no_passive_ep(struct fid_fabric *, struct fi_info *, struct fid_pep **, void *);
int lpp_fi_no_tx_ctx(struct fid_ep *, int, struct fi_tx_attr *, struct fid_ep **, void *);
int lpp_fi_no_rx_ctx(struct fid_ep *, int, struct fi_rx_attr *, struct fid_ep **, void *);
int lpp_fi_no_srx_context(struct fid_domain *, struct fi_rx_attr *, struct fid_ep **, void *);
int lpp_fi_no_scalable_ep_bind(struct fid_ep *sep, struct fid *fid, uint64_t flags);
int lpp_fi_no_pep_bind(struct fid_pep *pep, struct fid *fid, uint64_t flags);
ssize_t lpp_fi_no_cancel(fid_t, void *);
int lpp_fi_no_ep_alias(struct fid_ep *ep, struct fid_ep **alias_ep, uint64_t flags);
int lpp_fi_no_control(struct fid *, int, void *);
int lpp_fi_no_getopt(fid_t, int, int, void *, size_t *);
int lpp_fi_no_setopt(fid_t, int, int, const void *, size_t optlen);
ssize_t lpp_fi_no_rx_size_left(struct fid_ep *);
ssize_t lpp_fi_no_tx_size_left(struct fid_ep *);

//
// EQ
//
ssize_t lpp_fi_no_eq_write(struct fid_eq *, uint32_t, const void *, size_t, uint64_t);

//
// MSG
//
ssize_t lpp_fi_no_msg_recvv(struct fid_ep *, const struct iovec *, void **, size_t, fi_addr_t, void *);
ssize_t lpp_fi_no_msg_senddata(struct fid_ep *, const void *, size_t, void *, uint64_t, fi_addr_t, void *);
ssize_t lpp_fi_no_msg_injectdata(struct fid_ep *, const void *, size_t, uint64_t, fi_addr_t dest_addr);

//
// POLL
//
int lpp_fi_no_poll_open(struct fid_domain *, struct fi_poll_attr *, struct fid_poll **);
int lpp_fi_no_wait_open(struct fid_fabric *, struct fi_wait_attr *, struct fid_wait **);
int lpp_fi_no_trywait(struct fid_fabric *, struct fid **, int);

//
// RMA
//
ssize_t lpp_fi_no_rma_readv(struct fid_ep *, const struct iovec *, void **, size_t, fi_addr_t, uint64_t, uint64_t, void *);
ssize_t lpp_fi_no_rma_writev(struct fid_ep *, const struct iovec *, void **, size_t, fi_addr_t, uint64_t, uint64_t, void *);
ssize_t lpp_fi_no_rma_writedata(struct fid_ep *, const void *, size_t, void *, uint64_t, fi_addr_t, uint64_t, uint64_t, void *);
ssize_t lpp_fi_no_rma_injectdata(struct fid_ep *, const void *, size_t, uint64_t, fi_addr_t, uint64_t, uint64_t);

//
// TAGGED
//
ssize_t lpp_fi_no_tagged_recvv(struct fid_ep *, const struct iovec *, void **, size_t, fi_addr_t, uint64_t, uint64_t, void *);
ssize_t lpp_fi_no_tagged_sendv(struct fid_ep *, const struct iovec *, void **, size_t, fi_addr_t, uint64_t, void *);
ssize_t lpp_fi_no_tagged_search(struct fid_ep *, uint64_t *, uint64_t, uint64_t, fi_addr_t *, size_t *, void *);

#endif	// _LPP_ENOSYS_H_
