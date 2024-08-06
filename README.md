# ctx

ctx is C library providing a uniform interface to context switching facilities and stack allocation, similarly to ucontext. This library is geared towards the portable implementation of stackful coroutines.  

The supported triplets of `architecture-abi-assembler` are listed in the `arch` directory.

## building and dependency

ctx is currently built using the Meson build system. The `main.c` test file can be built as follows
```
meson setup bld
meson compile -C bld
```

To add ctx as a dependency to your project using the Meson build system, create a *wrap* file for ctx named `ctx.wrap` in a `subprojects` directory, with the following contents
```
[wrap-git]
url = git@github.com:aosync/ctx
revision = head
```
Then, the dependency can be added to your meson.build file using, typically, the following scheme
```
ctx_dep = dependency('ctx', required : false)
if not ctx_dep.found()
    ctx_proj = subproject('ctx')
    ctx_dep = ctx_proj.get_variable('ctx_dep')
endif
```
Finally, `ctx_dep` can be added as a dependency to your targets.

## credits

- [musl setjmp](http://git.musl-libc.org/cgit/musl/tree/src/setjmp/)
