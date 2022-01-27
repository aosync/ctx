#include "ctx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

thread_local struct ctx *_ctx_new = NULL;
thread_local void (*_ctx_fun)(void*) = NULL;
thread_local void *_ctx_args = NULL;

struct ctx{
#if defined(CTX_AMD64_SYSV)
	char regs[64]; /* rbx, rsp, rbp, r[4], rip */
#elif defined(CTX_AMD64_MS)
	char regs[240]; /* rbx, rbp, rdi, rsi, rsp, r[4], rip, xmm[10] */
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
	if (ctx == NULL)
		return NULL;
	memset(ctx, 0, sizeof(struct ctx));
	return ctx;
}

void
ctx_destroy(struct ctx *ctx)
{
	free(ctx);
}

void
ctx_switch(struct ctx *from, struct ctx *to)
{
	to->returnback = from;
	if(!ctx_save(from))
		ctx_jmp(to, 1);
}

void
_ctx_wrap(struct ctx *ctx, void (*fun)(void*), void *args)
{
	fun(args);
	ctx_switch(ctx, ctx->returnback);
}
