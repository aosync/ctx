#include "ctx.h"
#include <stdio.h>

void second() {
    printf("second\n");
}

void first() {
    second();
    printf("first\n");          // does not print
}

int main() {
    char *stack = malloc(8196);
    char *end = stack + 8196;
    struct ctx *ctx = ctx_create();


    struct ctx *back = ctx_create();
    ctx_link_to(ctx, end, (void (*)(void*))first, NULL);
    printf("got here\n");

    ctx_switch(back, ctx);

    ctx_destroy(back);
    ctx_destroy(ctx);
    free(stack);
    return 0;
}
