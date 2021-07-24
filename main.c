#include "ctx.h"
#include <stdio.h>

static struct ctx ctx;

void second() {
    printf("second\n");         // prints
    ctx_jmp(&ctx,1);             // jumps back to where setjmp was called - making setjmp now return 1
}

void first() {
    second();
    printf("first\n");          // does not print
}

int main() {   
    if (!ctx_save(&ctx))
        first();                // when executed, setjmp returned 0
    else                        // when longjmp jumps back, setjmp returns 1
        printf("main\n");       // prints

    return 0;
}
