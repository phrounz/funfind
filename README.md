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

   funfind processFile foo.c foo.h  # show the processFile function in foo.c or foo.h
   funfind void foo.c               # show functions returning void or having parameters with void in it
   funfind main foo.c               # show the main function in foo.c
   funfind "main(int argc" foo.c    # show the main function in foo.c (but only if it matches this pattern)
   funfind typedef foo.c            # show all typedefs on the global scope
   funfind "class Bar" foo.h        # show the Bar class definition/declaration (if it is on the global scope)
```

### Bugs
 * The program has still some troubles with \#ifdef.
