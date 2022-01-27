#include "ctx.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __OpenBSD__
#include <sys/mman.h>
#endif

void second() {
    printf("second\n");
}

void first(int *i) {
    second();
    printf("first %d\n", *i);          // does not print
}

int main() {
    #ifdef __OpenBSD__
    char *stack = mmap(NULL, 1024*9, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_STACK|MAP_ANON, -1, 0);
    #else
    char *stack = malloc(1024*9);
    #endif
    char *end = stack + 8196;
    struct ctx *ctx = ctx_create();

    int i = 43;


    struct ctx *back = ctx_create();
    ctx_link_to(ctx, end, (void (*)(void*))first, &i);
    printf("got here\n");

    ctx_switch(back, ctx);

    ctx_destroy(back);
    ctx_destroy(ctx);
    #ifdef __OpenBSD__
    munmap(stack, 1024*9);
    #else
    free(stack);
    #endif
    return 0;
}
