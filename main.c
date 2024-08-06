#include "ctx.h"
#include <stdio.h>
#include <stdlib.h>

void first(int *i) {
    printf("Called %d\n", *i);
    *i += 27;
}

int main() {
    int i = 42;

    // Initiate the stack
    struct ctx_stack stack;
    ctx_stack_init(&stack, 8 * 1024);
    printf("Created stack %p %p\n", stack.low, stack.high);

    // Create the foreign ctx and link it to the stack and function
    struct ctx *ctx = ctx_create();
    ctx_link(ctx, &stack, (void (*)(void*))first, &i);
    printf("Linked!\n");

    // Create the ctx for the current context
    struct ctx *back = ctx_create();

    // Switch to the foreign ctx
    ctx_switch(back, ctx);

    // ... foreign ctx yields back automatically when it returns
    printf("Returned to parent! %d\n", i);

    // Destroy the contexts
    ctx_destroy(back);
    ctx_destroy(ctx);

    // Deallocate the stack
    ctx_stack_finish(&stack);

    printf("Finished all!\n");
    return 0;
}
