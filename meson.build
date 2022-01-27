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
	'x86_64_linux': 'amd64_sysv',
	'x86_64_freebsd': 'amd64_sysv',
	'x86_64_dragonflybsd': 'amd64_sysv',
	'x86_64_netbsd': 'amd64_sysv',
	'x86_64_openbsd': 'amd64_sysv',
	'x86_64_windows': 'amd64_ms',
}

assemblers = {
	'x86_64_msvc': ['ml64', '.asm', ml64_as],
	'x86_64_gcc': ['as', '.s', as_as],
	'x86_64_clang': ['as', '.s', as_as]
}

# get ABI string
cpu = target_machine.cpu_family()
os = target_machine.system()
abi = abis[cpu + '_' + os]

# get environment's assembler
cc = meson.get_compiler('c')
assembler = assemblers[cpu + '_' + cc.get_id()]

# get asm source path
asm_path = abi + '_' + assembler[0]

ctx_sources = [
	    'ctx.c'
]

ctx_asm_sources = [
	'arch' / asm_path / 'ctx_save' + assembler[1],
	'arch' / asm_path / 'ctx_jmp' + assembler[1]
]


ctx_asm_obj = assembler[2].process(ctx_asm_sources)

message('ctx: using abi', asm_path)

ctx_inc = include_directories('.')
ctx_lib = static_library('ctx', ctx_sources, ctx_asm_obj, include_directories : ctx_inc, c_args : [('-DCTX_' + abi).to_upper()])
ctx_dep = declare_dependency(link_with : ctx_lib, include_directories : ctx_inc)

executable('ctxmain', 'main.c', dependencies : ctx_dep)
