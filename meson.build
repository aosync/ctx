project('ctx', 'c')

abidict = {
	'x86_64_linux': 'amd64_sysv',
	'x86_64_freebsd': 'amd64_sysv',
	'x86_64_dragonflybsd': 'amd64_sysv',
	'x86_64_netbsd': 'amd64_sysv',
	'x86_64_openbsd': 'amd64_sysv',
	'x86_64_windows': 'amd64_ms',
}

asdict = {
	'x86_64_msvc': ['masm', '.asm'],
	'x86_64_gcc': ['as', '.s'],
	'x86_64_clang': ['as', '.s']
}

cpu = target_machine.cpu_family()
os = target_machine.system()
abi = abidict['@0@_@1@'.format(cpu, os)]

cc = meson.get_compiler('c')
as = asdict['@0@_@1@'.format(cpu, cc.get_id())]

asname = '@0@_@1@'.format(abi, as[0])

ctx_sources = [
	    'arch' / asname / 'ctx_save' + as[1],
	    'arch' / asname / 'ctx_jmp' + as[1],
	    'ctx.c'
]

ctx_inc = include_directories('.')
ctx_lib = static_library('ctx', ctx_sources, include_directories : ctx_inc, c_args : ['-DCTX_@0@'.format(abi).to_upper()])
ctx_dep = declare_dependency(link_with : ctx_lib, include_directories : ctx_inc)

executable('ctxmain', 'main.c', dependencies : ctx_dep)