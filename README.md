## funfind
Show the body of a function (and other stuff on global scope) in C/C++ source files.

Source under [MIT license](./LICENSE).

### Compilation
```
   gcc funfind.c -o funfind
```

### Syntax and examples

```
   funfind <pattern> <file-1> [<file-2> [...]]

   funfind void foo.c foo.h      # show everything void on the global scope in foo.c foo.h
   funfind main foo.c            # show the main function in foo.c
   funfind typedef foo.c         # show typedefs on the global scope
   funfind "main(int argc" foo.c # show the stuff in global scope which has pattern "main(int argc"
   funfind "class Bar" foo.hh    # show class Bar on the global scope
```

### Bugs
The program has still some troubles with \#ifdef
