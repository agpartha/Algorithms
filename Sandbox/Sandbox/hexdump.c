#include <ctype.h>
#include <stdio.h>

void hexdump(void *ptr, int buflen) {
  unsigned char *buf = (unsigned char*)ptr;
  int i, j;
  for (i=0; i<buflen; i+=16) {
    printf("%06x: ", i);
    for (j=0; j<16; j++) 
      if (i+j < buflen)
        printf("%02x ", buf[i+j]);
      else
        printf("   ");
    printf(" ");
    for (j=0; j<16; j++) 
      if (i+j < buflen)
        printf("%c", isprint(buf[i+j]) ? buf[i+j] : '.');
    printf("\n");
  }
}

int main (int argc, char **argv)
{
    unsigned char data[32] = {'A'};

    data[0] = 0;
    data[1] = 1;
    data[2] = 'A';
    data[3] = 'U';
    data[4] = 'B';
    data[5] = 'I';
    data[6] = 'N';
    data[7] = ' ';

    hexdump(data, sizeof(data));
    
    return 0;
}
