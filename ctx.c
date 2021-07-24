#include "ctx.h"

_Thread_local struct ctx ctx_get_back;
_Thread_local struct ctx ctx_new;


void
ctx_switch(struct ctx *from, struct ctx *to)
{
	if(!ctx_save(from)){
		ctx_jmp(to, 1);
	}
}
