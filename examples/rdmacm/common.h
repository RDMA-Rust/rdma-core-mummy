/*
 * Copyright (c) 2005-2012 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
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
 *
 * $Id$
 */

#include <endian.h>
#include <poll.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include <infiniband/ib.h>
#include <rdma/rdma_cma.h>

union socket_addr {
	struct sockaddr sa;
	struct sockaddr_in sin;
	struct sockaddr_in6 sin6;
};

enum rs_optimization { opt_mixed, opt_latency, opt_bandwidth };

int get_rdma_addr(const char *src, const char *dst, const char *port,
		  struct rdma_addrinfo *hints, struct rdma_addrinfo **rai);

int oob_server_setup(const char *src_addr, const char *port, int *sock);
int oob_client_setup(const char *dst_addr, const char *port, int *sock);
int oob_sendrecv(int sock, char val);
int oob_recvsend(int sock, char val);

void size_str(char *str, size_t ssize, long long size);
void cnt_str(char *str, size_t ssize, long long cnt);
int size_to_count(int size);
void format_buf(void *buf, int size);
int verify_buf(void *buf, int size);
int do_poll(struct pollfd *fds, int timeout);

struct rdma_event_channel *create_event_channel(void);

static inline uint64_t gettime_ns(void)
{
	struct timespec now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	return now.tv_sec * 1000000000 + now.tv_nsec;
}

static inline uint64_t gettime_us(void)
{
	return gettime_ns() / 1000;
}

static inline int sleep_us(unsigned int time_us)
{
	struct timespec spec;

	if (!time_us)
		return 0;

	spec.tv_sec = 0;
	spec.tv_nsec = time_us * 1000;
	return nanosleep(&spec, NULL);
}

struct work_item {
	struct work_item *next;
	void (*work_handler)(struct work_item *item);
};

struct work_queue {
	pthread_mutex_t lock;
	pthread_cond_t cond;

	pthread_t *thread;
	int thread_cnt;
	bool running;

	struct work_item *head;
	struct work_item *tail;
};

int wq_init(struct work_queue *wq, int thread_cnt);
void wq_cleanup(struct work_queue *wq);
void wq_insert(struct work_queue *wq, struct work_item *item,
	       void (*work_handler)(struct work_item *item));
struct work_item *wq_remove(struct work_queue *wq);

#define container_of(ptr, type, member)                                        \
	({                                                                     \
		const typeof(((type *)0)->member) *__mptr = (ptr);             \
		(type *)((char *)__mptr - offsetof(type, member));             \
	})
