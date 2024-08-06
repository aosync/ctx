#include "ctx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#endif

struct ctx {
#if defined(CTX_X86_64_SYSV)
	char regs[64]; /* rbx, rsp, rbp, r[4], rip */
#elif defined(CTX_X86_64_MS)
	char regs[264]; /* rbx, rbp, rdi, rsi, rsp, r[4], rip, xmm[10], stack {high,low,guard} */
#endif
	struct ctx *returnback;
};


void ctx_link_to(struct ctx *ctx, char *stackd[], void (*fun)(void*), void *args);
void _ctx_wrap(struct ctx *ctx, void (*fun)(void*), void *args);

struct ctx *
ctx_create(void)
{
	struct ctx *ctx = malloc(sizeof(struct ctx));
	if (ctx == NULL)
		return NULL;

	*ctx = (struct ctx) {};
	
	return ctx;
}

void
ctx_destroy(struct ctx *ctx)
{
	free(ctx);
}

void
ctx_link(struct ctx *ctx, struct ctx_stack *stack, void (*fun)(void*), void *args)
{
	char *stackd[3] = {stack->high, stack->low, stack->guard};
	ctx_link_to(ctx, stackd, fun, args);
}

void
ctx_switch(struct ctx *from, struct ctx *to)
{
	to->returnback = from;
	if (!ctx_save(from))
		ctx_jmp(to, 1);
}

void
_ctx_wrap(struct ctx *ctx, void (*fun)(void*), void *args)
{
	fun(args);
	ctx_switch(ctx, ctx->returnback);
}

static size_t page_size()
{
#ifdef _WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwPageSize;
#else
    return sysconf(_SC_PAGESIZE);
#endif
}

void
ctx_stack_init(struct ctx_stack *stack, size_t size)
{
	size_t page = page_size();
	size = (size + page - 1) / page * page;

#ifdef _WIN32
	char *guard = VirtualAlloc(NULL, size + page, MEM_COMMIT, PAGE_READWRITE);
	char *low = guard + page;
#else
	char *guard = (char*)mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE|MAP_STACK, -1, 0);
	char *low = guard;
#endif

	*stack = (struct ctx_stack) {
		.high = low + size,
		.low = low,
		.guard = guard,
	};
}

void
ctx_stack_finish(struct ctx_stack *stack)
{
#ifdef _WIN32
	VirtualFree(stack->guard, 0, MEM_DECOMMIT | MEM_RELEASE);
#else
	munmap(stack->guard, (size_t)(stack->high - stack->guard));
#endif
}