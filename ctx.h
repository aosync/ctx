#ifndef CTX_H
#define CTX_H

#include <stdlib.h>
#include <stdint.h>

#define CTX_STACK_HIGH 0
#define CTX_STACK_LOW 1
#define CTX_STACK_GUARD 2
struct ctx_stackd {
	char *stack_addr[3];
};

struct ctx;

/*	struct ctx has to be opaque because of the different ABIs,
	so allocation functions are provided */
size_t ctx_ctx_size(void);
struct ctx *ctx_create(void);
void ctx_destroy(struct ctx *ctx);

void ctx_link_to(struct ctx *ctx, struct ctx_stackd *stackd, void (*fun)(void*), void *args);
void ctx_jmp(struct ctx *ctx, int sig);
int ctx_save(struct ctx *ctx);
void ctx_switch(struct ctx *from, struct ctx *to);
void _ctx_wrap(struct ctx *ctx, void (*fun)(void*), void *args);

#endif
