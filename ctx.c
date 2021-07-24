#include "ctx.h"

void
ctx_switch(struct ctx *from, struct ctx *to)
{
	if(!ctx_save(from)){
		ctx_jmp(to, 1);
	}
}
