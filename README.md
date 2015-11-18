## funfind
Show the definition or declaration of a function (and other stuff on global scope) in C/C++ source files.

Source under [MIT license](./LICENSE).

### Compilation
```
   gcc funfind.c -o funfind
```

### Syntax and examples

```
   funfind <pattern> <file-1> [<file-2> [...]]

   funfind void foo.c foo.h      # show functions returning void or having void* parameters in foo.c foo.h
   funfind main foo.c            # show the main function in foo.c
   funfind typedef foo.c         # show typedefs on the global scope
   funfind "main(int argc" foo.c # show the main function in foo.c but only if it matches this pattern
   funfind "class Bar" foo.hh    # show the Bar class definition/declaration (if it is on the global scope)
```

### Bugs
 * The program has still some troubles with \#ifdef.
