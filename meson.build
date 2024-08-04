project('ctx', 'c')

ml64 = find_program('ml64', required : false)
ml64_as = generator(ml64,
	output : '@BASENAME@.obj',
	arguments : [
		'/Fo', '@OUTPUT@',
		'/c', '@INPUT@'])

as = find_program('as', required : false)
as_as = generator(as,
	output : '@BASENAME@.o',
	arguments : [
		'@INPUT@',
		'-o', '@OUTPUT@'])

abis = {
	'x86_64-linux': 'sysv',
	'x86_64-freebsd': 'sysv',
	'x86_64-dragonflybsd': 'sysv',
	'x86_64-netbsd': 'sysv',
	'x86_64-openbsd': 'sysv',
	'x86_64-windows': 'ms',
}

assemblers = {
	'x86_64-msvc': ['ml64', '.asm', ml64_as],
	'x86_64-gcc': ['as', '.s', as_as],
	'x86_64-clang': ['as', '.s', as_as]
}

# get ABI string
cpu = target_machine.cpu_family()
os = target_machine.system()
abi = abis[cpu + '-' + os]

# get environment's assembler
cc = meson.get_compiler('c')
assembler = assemblers[cpu + '-' + cc.get_id()]

# get asm source path
asm_path = cpu + '-' + abi + '-' + assembler[0]

ctx_sources = [
	'ctx.c'
]

ctx_asm_sources = [
	'arch' / asm_path / 'ctx_save' + assembler[1],
	'arch' / asm_path / 'ctx_jmp' + assembler[1],
	'arch' / asm_path / 'ctx_link_to' + assembler[1]
]

ctx_asm_obj = assembler[2].process(ctx_asm_sources)

message('ctx: using abi', asm_path)

ctx_inc = include_directories('.')
ctx_lib = static_library('ctx', ctx_sources, ctx_asm_obj, include_directories : ctx_inc, c_args : [('-DCTX_' + cpu + '_' + abi).to_upper()])
ctx_dep = declare_dependency(link_with : ctx_lib, include_directories : ctx_inc)

executable('ctxmain', 'main.c', dependencies : ctx_dep)
