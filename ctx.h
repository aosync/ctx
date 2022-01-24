#ifndef CTX_H
#define CTX_H

#include <stdlib.h>
#include <stdint.h>
#include <threads.h>

struct ctx{
#if defined(__amd64__)
#define ctx_stack_to(x) asm volatile ("mov %0, %%rsp" : : "r"(x))
	char regs[64]; /* rbx, rsp, rbp, r[4], rip */
#endif
	struct ctx *returnback;
};

extern thread_local struct ctx *_ctx_new;
extern thread_local void (*_ctx_fun)(void*);
extern thread_local void *_ctx_args;


void ctx_link_to(struct ctx *ctx, char *stack, void (*fun)(void*), void *args);
void ctx_jmp(struct ctx *ctx, int sig);
int ctx_save(struct ctx *ctx);
void ctx_switch(struct ctx *from, struct ctx *to);
void _ctx_wrap();

#endif
