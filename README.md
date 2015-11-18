## funfind
Very simple command-line program displaying the definition or the declaration of something on global scope, in C/C++ source files.

Works on Linux, Windows, using gcc. Port to other compilers or operating systems is probably easy.

Source under [MIT license](./LICENSE).

### Compilation

```
   gcc funfind.c -o funfind
```

### Syntax and examples

```
   funfind <pattern> <file-1> [<file-2> [...]]

   # show the main function in foo.c
   funfind main foo.c         
   
   ---> will display for example:
       int main(int argc, char* argv[])
       {
         printf("Hello world\n");
         return 0;
       }
   
   # show the processFile function in foo.c or foo.h
   funfind processFile foo.c foo.h  
   
   # show functions returning void or having parameters with void or voidOfTheUniverse in it
   funfind void foo.c
   
   # show the main function in foo.c (but only if it matches this pattern)
   funfind "main(int argc" foo.c    
   
   # show all typedefs on the global scope
   funfind typedef foo.c            
   
   # show the Bar class definition/declaration (if it is on the global scope)
   funfind "class Bar" foo.h
```

### Bugs
 * The program has still some troubles with \#ifdef.
