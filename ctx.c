#include "ctx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

thread_local struct ctx *_ctx_new = NULL;
thread_local void (*_ctx_fun)(void*) = NULL;
thread_local void *_ctx_args = NULL;

struct ctx{
#if defined(__amd64__)
#define ctx_stack_to(x) asm volatile ("mov %0, %%rsp" : : "r"(x))
	char regs[64]; /* rbx, rsp, rbp, r[4], rip */
#endif
	struct ctx *returnback;
};

size_t
ctx_ctx_size(void)
{
	return sizeof(struct ctx);
}

struct ctx *
ctx_create(void)
{
	struct ctx *ctx = malloc(sizeof(struct ctx));
	memset(ctx, 0, sizeof(struct ctx));
	return ctx;
}

void
ctx_destroy(struct ctx *ctx)
{
	free(ctx);
}

void
ctx_link_to(struct ctx *ctx, char *stack, void (*fun)(void*), void *args)
{
	_ctx_new = ctx;
	_ctx_fun = fun;
	_ctx_args = args;

	struct ctx link;

	struct ctx *prev_returnback = ctx->returnback;
	ctx->returnback = &link;

	if(!ctx_save(&link)){
		ctx_stack_to(stack);
		_ctx_wrap();
	}

	ctx->returnback = prev_returnback;
	_ctx_fun = NULL;
	_ctx_args = NULL;
	_ctx_new = NULL;
}

void
ctx_switch(struct ctx *from, struct ctx *to)
{
	to->returnback = from;
	if(!ctx_save(from))
		ctx_jmp(to, 1);
}

void
_ctx_wrap()
{
	void (*fun)(void*) = _ctx_fun;
	void *args = _ctx_args;
	struct ctx *this_ctx = _ctx_new;

	ctx_switch(this_ctx, this_ctx->returnback);
	fun(args);
	ctx_switch(this_ctx, this_ctx->returnback);
}