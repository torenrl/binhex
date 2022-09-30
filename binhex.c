#include <stdio.h>
#include <stdlib.h>

int xtoi(char *x) {
  int base=10;
  char *ptr;
  if ( x[1] == 'x' ) {
    base=16;
    ptr=x+2;
  }
  else if ( x[1] == 'b' ) {
    base=2;
    ptr=x+2;
  }
  else if ( x[1] == 'd' ) {
    base=10;
    ptr=x+2;
  }
  else {
    base=10;
    ptr=x;
  }
  return strtol(ptr, NULL, base);
;
}

void printbin(int n, int nbits) {
  for ( int i = nbits-1 ; i >= 0 ; i-- ) {
    printf("%d", (n&(1<<i))?1:0);
  }
}

int main(int argc, char **argv) {

  int start = 0;
  int end = 0;

  if ( argc > 2 ) {
    start = xtoi(argv[1]);  
    end   = xtoi(argv[2]);
  }
  else if ( argc > 1 ) {
    start = xtoi(argv[1]);
    end   = start;
  }
  
  int nbits = 0;
  int temp = end;
  
  while( temp ) {
    nbits++;
    temp >>= 1;
  }

  if ( !nbits ) {
    nbits = 1;
  }

  int ntens = 0;
  temp = end;
  while ( temp ) {
    ntens++;
    temp /= 10;
  }

  int nhex = nbits/4;
  nhex += (nhex%4)?1:0; 

  end += 1;

  if (ntens<3) {
    ntens=3;
  }

  printf("%-*s %-*s %-*s\n", ntens, "DEC", nbits, "BIN", nhex, "HEX");

  for ( int i = start ; i < end ; i++ ) {
    printf("%*d ", ntens, i);
    printbin(i,nbits);
    printf(" %0*X\n", nhex, i);
  }


  return 0;
}