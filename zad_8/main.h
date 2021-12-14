/* ******************** LIBRARIES ******************** */

#include <stdio.h>
#include <stdlib.h>

// If MSVC complained; works fine for GCC as simple #include "../utils/utils.c"
#ifdef __linux__
  #include "../utils/utils.c" /* utils for linux */
#elif _WIN32
  #include "..\utils\utils.c" /* utils for windows */
#endif


/* ******************** PROTOTYPES ******************** */