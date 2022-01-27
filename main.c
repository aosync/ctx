#include "ctx.h"
#include <stdio.h>

#include <sys/mman.h>

void second() {
    printf("second\n");
}

void first() {
    second();
    printf("first\n");          // does not print
}

int main() {
    char *stack = mmap(NULL, 1024*9, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_STACK|MAP_ANON, -1, 0);
    char *end = stack + 8196;
    size_t endi = (size_t)end;
    endi = (endi - 8) & ~0xF;
    end = (char*)endi;
    struct ctx *ctx = ctx_create();


    struct ctx *back = ctx_create();
    ctx_link_to(ctx, end, (void (*)(void*))first, NULL);
    printf("got here\n");

    ctx_switch(back, ctx);

    ctx_destroy(back);
    ctx_destroy(ctx);
    munmap(stack, 1024*9);
    return 0;
}
