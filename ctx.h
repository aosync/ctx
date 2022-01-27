#ifndef CTX_H
#define CTX_H

#include <stdlib.h>
#include <stdint.h>
#include "threadlocal.h"

struct ctx;

extern thread_local struct ctx *_ctx_new;
extern thread_local void (*_ctx_fun)(void*);
extern thread_local void *_ctx_args;


/*	struct ctx has to be opaque because of the different ABIs,
	so allocation functions are provided */
size_t ctx_ctx_size(void);
struct ctx *ctx_create(void);
void ctx_destroy(struct ctx *ctx);

void ctx_link_to(struct ctx *ctx, char *stack, void (*fun)(void*), void *args);
void ctx_jmp(struct ctx *ctx, int sig);
int ctx_save(struct ctx *ctx);
void ctx_switch(struct ctx *from, struct ctx *to);
void _ctx_wrap(struct ctx *ctx, void (*fun)(void*), void *args);

#endif
