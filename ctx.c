#include "ctx.h"

#include <stdio.h>

_Thread_local struct ctx *_ctx_new = NULL;
_Thread_local void (*_ctx_fun)(void*) = NULL;
_Thread_local void *_ctx_args = NULL;

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
	if(!ctx_save(from)){
		ctx_jmp(to, 1);
	}
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