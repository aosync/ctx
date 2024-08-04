#ifndef CTX_H
#define CTX_H

#include <stddef.h>

struct ctx_stack {
	char *high;
	char *low;
};

struct ctx;

struct ctx *ctx_create(void);
void ctx_destroy(struct ctx *ctx);

void ctx_link(struct ctx *ctx, struct ctx_stack *stack, void (*fun)(void*), void *args);
void ctx_jmp(struct ctx *ctx, int sig);
int ctx_save(struct ctx *ctx);
void ctx_switch(struct ctx *from, struct ctx *to);

void ctx_stack_init(struct ctx_stack *stack, size_t size);
void ctx_stack_finish(struct ctx_stack *stack);

#endif
