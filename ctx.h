#ifndef CTX_H
#define CTX_H

#include <stdlib.h>
#include <stdint.h>

struct ctx{
#if defined(__amd64__)
#define ctx_stack_to(x) asm volatile ("mov %0, %%rsp" : : "r"(x))
	uint64_t rbx, rsp, rbp, r[4], rip;
#endif
};


void ctx_jmp(struct ctx *ctx, int sig);
int ctx_save(struct ctx *ctx);
void ctx_switch(struct ctx *from, struct ctx *to);

#endif
