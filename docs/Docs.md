This project isn't finished so no documentation yet


## Including

To include this into your own C++ project:
- clone this repository
- build the library using `make lib`
- copy `bin/libtui.s` into directory of your project
- copy `src/lib.h` file into directory of your project
- insert `#include "path/to/lib.h"` into your cpp file that includes this library
- include `libtui.s` to compiler. Different for different compilers. for `gcc`, use `-Lirectory -ltui` where directory is the path to `libtui.s`
  - For example: `gcc main.c -o program -Llibs -ltui`