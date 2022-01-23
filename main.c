#include "ctx.h"
#include <stdio.h>

static struct ctx ctx;

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

    struct ctx back;
    ctx_link_to(&ctx, end, (void (*)(void*))first, NULL);

    ctx_switch(&back, &ctx);

    free(stack);
    return 0;
}
