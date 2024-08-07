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

#ifndef _LPP_RX_H_
#define _LPP_RX_H_


#include "lpp_completion.h"

#define LPP_RX_ENTRY_CQ_RSRV	(0x01UL)
#define LPP_RX_ENTRY_GPU	(0x02UL) // can drop for rx_entry->hmem_iface?
#define LPP_RX_ENTRY_MR		(0x04UL)

struct lpp_rx_entry {
	struct dlist_entry	dle;
	uint64_t		flags;
	uint64_t		lpp_flags;
	struct iovec		msg_iov[KLPP_MAX_RECV_IOVS];
	size_t			iov_count;
	size_t			total_length;
	size_t			overflow_length;
	fi_addr_t		addr;
	uint64_t		tag;
	uint64_t		data;
	uint64_t		ignore;
	void			*context;
	size_t			offset;
	struct dlist_entry	pending_ops;
	Lpp_mr_t		*mrp;
	enum fi_hmem_iface	hmem_iface;
};

#define LPP_RX_OP_ONLIST	(0x01UL)
#define LPP_RX_OP_MUSTFREE	(0x02UL)

struct lpp_rx_op {
	struct dlist_entry	dle;
	struct lpp_rx_entry	*rx_entry;
	uint64_t		lpp_flags;
	size_t			length;
	uint64_t		tag;
	uint64_t		overflow_length;
	size_t			offset;
	void			*buf;
	union lpp_fi_addr_storage src_addr;
	enum fi_hmem_iface	hmem_iface;
};

struct lpp_rx_unexp_msg {
	struct dlist_entry	dle;
	void			*claim_context;
	struct klpp_msg_hdr	hdr[];
};

typedef struct _lpp_rx {
	struct fid_ep		rx_fid;
	struct fi_rx_attr	attr;

	Lpp_ep_t		*ep;
	Lpp_cq_t		*cq;
	Lpp_cntr_t		*cntr;
	Lpp_domain_t		*domain;

	ofi_atomic32_t		ref_count;

	Lpp_ctx_t		ctx;

	klpp_id_t		id;
	int			is_enabled;
	size_t			min_multi_recv;

	struct lpp_rx_entry	*rx_entries;
	struct dlist_entry	rx_entry_freelist;
	// TODO: make a separate list for tagged msgs
	struct dlist_entry	posted_rxs;
	struct dlist_entry	unexp_msgs;
	struct dlist_entry	unexp_claimed_msgs;
} Lpp_rx_t;

void			lpp_rx_bind_ep(Lpp_rx_t *lpp_rxp, Lpp_ep_t *lpp_epp);
void			lpp_rx_bind_cq(Lpp_rx_t *lpp_rxp, Lpp_cq_t *lpp_cqp);
void			lpp_rx_bind_cntr(Lpp_rx_t *lpp_rxp, Lpp_cntr_t *lpp_cntrp);

void			lpp_rx_unbind_ep(Lpp_rx_t *lpp_rxp);
void			lpp_rx_unbind_cq(Lpp_rx_t *lpp_rxp);
void			lpp_rx_unbind_cntr(Lpp_rx_t *lpp_rxp);

struct fi_rx_attr	lpp_rx_attrs(const struct klppioc_lf *klpp_devinfo);
int			lpp_verify_rx_attrs(const struct klppioc_lf *klpp_devinfo, struct fi_rx_attr *rx_attrs);

Lpp_rx_t		*lpp_rx_context(Lpp_ep_t *lpp_epp, struct fi_rx_attr *attr);
int			lpp_rx_close(Lpp_rx_t *lpp_rxp);

ssize_t lpp_rx_common(Lpp_ep_t *lpp_epp, struct lpp_rx_entry *rx_entry);
struct lpp_rx_entry *lpp_rx_entry_get(Lpp_rx_t *lpp_rxp);
int lpp_rx_process_msg(Lpp_ep_t *lpp_epp, struct klpp_msg_hdr *hdr);
ssize_t lpp_rx_verify_iov_count(Lpp_rx_t *lpp_rxp, size_t iov_count);
ssize_t lpp_rx_verify_flags(Lpp_rx_t *lpp_rxp, uint64_t flags);
void lpp_rx_rdzv_done(Lpp_ep_t *lpp_epp, struct klpp_umc_k2u *k2u);
int lpp_rx_cancel(Lpp_ep_t *lpp_epp, void *context);

#endif //  _LPP_RX_H_
