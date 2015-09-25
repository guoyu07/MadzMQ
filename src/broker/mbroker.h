#ifndef _MBROKER_H_INCLUDED_
#define _MBROKER_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include "czmq.h"
#include "mbroute.h"
#include "mbpublish.h"
#include "mbqueue.h"

typedef struct _mbroker_t mbroker_t;

struct _mbroker_t
{
	zctx_t *ctx;
	mbroute_t *client_route;
	mbqueue_t *queue;
	mbpublish_t *publish;
	mbroute_t *snapshot;
	mbroute_t *service_route;
	void *service;
	//mbstats_t *stats;
	zhash_t *kvmap;
	int64_t sequence;
	zloop_t *loop;
	bool verbose;
};

typedef struct {
	void *socket;
	zframe_t *identity;
	char *subtree;
} kvroute_t;

#define MBROKER_HOST 			"127.0.0.1"
#define MBROUTE_CLIENT_HOST		"127.0.0.1"
#define MBROUTE_CLIENT_PORT		5555
#define SNAPSHOT_HOST			"127.0.0.1"
#define SNAPSHOT_PORT			5556
#define MBPUBLISH_HOST			"127.0.0.1"
#define MBPUBLISH_PORT			5557

#define CLIENT_ROUTE_MODE		1
#define SNAPSHOT_MODE			2

mbroker_t *mbroker_new();
void mbroker_destroy(mbroker_t **this_p);

void mbroker_loop_poller(mbroker_t *this, zloop_fn handler, int mode);
void mbroker_loop_timer(mbroker_t *this, size_t delay, size_t time,  zloop_timer_fn handler);
void mbroker_looper(mbroker_t *this);

int s_send_single(const char *key, void *data, void *args);

int client_route_recv_handle(zloop_t *loop, zmq_pollitem_t *poller, void *args);
int snapshot_handle(zloop_t *loop, zmq_pollitem_t *pooler, void *args);
int publish_send_handle(zloop_t *loop, zmq_pollitem_t *poller, void *args);

#ifdef __cplusplus
}
#endif

#endif