
#include <stdio.h>

struct abc {
    int    (*test_fp)(void);
};

int main (void)
{
    struct abc  def; 
    
    printf ("sizeof %d\n", sizeof(*def.test_fp));
}
