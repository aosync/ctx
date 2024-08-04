#include "ctx.h"
#include <stdio.h>
#include <stdlib.h>

void first(int *i) {
    printf("Called %d\n", *i);
}

int main() {
    int i = 42;

    // Initiate the stack
    struct ctx_stack stack;
    ctx_stack_init(&stack, 8 * 1024);

    // Create the foreign ctx and link it to the stack and function
    struct ctx *ctx = ctx_create();
    ctx_link(ctx, &stack, (void (*)(void*))first, &i);
    printf("Linked!\n");

    // Create the ctx for the current context
    struct ctx *back = ctx_create();

    // Switch to the foreign ctx
    ctx_switch(back, ctx);

    // ... foreign ctx yields back automatically when it returns

    // Destroy the contexts
    ctx_destroy(back);
    ctx_destroy(ctx);

    // Deallocate the stack
    ctx_stack_finish(&stack);
    return 0;
}
