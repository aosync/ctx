project('ctx', 'c')

cpu = target_machine.cpu_family()

ctx_sources = [
	    'arch' / cpu / 'ctx_save.s',
	    'arch' / cpu / 'ctx_jmp.s',
	    'ctx.c'
]

ctx_inc = include_directories('.')
ctx_lib = static_library('ctx', ctx_sources, include_directories : ctx_inc)
ctx_dep = declare_dependency(link_with : ctx_lib, include_directories : ctx_inc)

executable('ctxmain', 'main.c', dependencies : ctx_dep)