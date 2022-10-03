#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  int xtoi ( char* x)
 *  Converting a number string to integer
 *  
 *  inputs  
 *       x: pointer to a string containing a number in decimal,
 *          hex or bin format.
 *
 *  intput format: 
 *          A decimal number  XXX
 *          A decimal number  0dXXX
 *          A hex number      0xXXX
 *          A bin number      0bXXX
 *          An exp number     X.XXeXX
 *
 *  output: the number as int
 */
long xtoi(char *x) {
  int done = 0;
  long ret = 0;
  int base=10;
  char *ptr;
  int exp = 0;
  double num = 0;
  int i = 0;

  if ( x[1] == 'e' || (x[1] >= '0' && x[1] <= '9') ) {
    while ( x[i] != '\0' ) {
      if ( x[i] == 'e' || x[i] == 'E' ) {
        x[i] = '\0';
        num = strtod(x, NULL);
        exp = strtol(x+1+i, NULL, 10);
        printf("%lf*10^%d", num, exp);
        for ( int j = 0 ; j < exp ; ++j ) num *= 10;
        ret = (long)num;
        done = 1;
      }
      else i++;
    }
  }

  if ( !done ) {
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
    ret = strtol(ptr, NULL, base);
  } 
  return ret;
}

/*  printbin( int n, int nbits )
 *  Printing the nbits lsb's of the integer n in binary format
 *
 */
void printbin(long n, int nbits, int space) {
  for ( int i = nbits-1 ; i >= 0 ; i-- ) {
    printf("%d", (n&((long)1<<i))?1:0);
  }
  for ( int i = nbits; i < space; i++ ) {
    printf(" ");
  }
}

int main(int argc, char **argv) {

  long start = 0;
  long end = 0;

  long mostbits = 0;

  if ( argc > 2 ) {
    start = xtoi(argv[1]);  
    end   = xtoi(argv[2]);
  }
  else if ( argc > 1 ) {
    start = xtoi(argv[1]);
    end   = start;
  }

  int nbits=1;


  if ( start < 0 ) {
    mostbits = -start;
    if ( mostbits < end ) {
      mostbits = end;
    }
  } 
  else {
    mostbits = end;
  }


  for ( int i = 0 ; i < 64 ; ++i ) {
    if ( mostbits&((long)(1)<<i) ) {
      nbits = i+1;
    }
  }
  if ( start < 0 ) nbits++;

  int ntens = 1;
  unsigned long temp = mostbits;
  while ( temp/=10 ) {
    ntens++;
  }
  if ( start<0 ) {
    ntens++;
  }  
  if (ntens<3) {
    ntens=3;
  }

  int nhex = nbits/4;
  nhex += ((nbits%4) != 0);

  end += 1;

  printf("\nNumber of bits needed: %d\n\n", nbits);

  printf("%-*s  %-*s  %-*s  %-*s\n", nbits, "BIN", nhex, "HEX", ntens, "DEC", ntens, "UNSIGNED DEC");

  unsigned long mask = 0;
  for ( int i = 0 ; i < nbits ; ++i ) {
    mask |= 1<<i;
  }

  for ( long i = start ; i < end ; i++ ) {

    printbin(i,nbits, (nbits<3)?3:nbits);
    printf("  %0*lX%*.s", nhex, i&mask, 2+((3-nhex)<0?0:3-nhex), "     ");
    printf("%-*ld  ", ntens, i);
    printf("%-*ld\n", ntens, (unsigned long)i);
  }

  printf("\n");
  
  return 0;
}
