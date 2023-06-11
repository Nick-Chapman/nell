#include <stdio.h>
#include <stdlib.h>

int fib(int i) {
  if (i < 2) return i;
  return fib(i-1) + fib(i-2);
}

int main(int argc, char* argv[]) {
  int arg = argc>1 ? atoi(argv[1]) : 2;
  int res = fib(arg);
  printf("fib(%d) -> %d\n",arg,res);
  return 0;
}
