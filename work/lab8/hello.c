#include <stdio.h>
#include <stdlib.h>

int
main(int argc, const char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "usage: %s NAME...\n", argv[0]);
    exit(1);
  }
//<<<<<<< HEAD
  for (int i = 1; i < argc; i++) {
    printf("hello %s\n", argv[i]);
  }
//=======
  printf("hello %s\n", argv[1]);
  return 0;
//>>>>>>> master
}
