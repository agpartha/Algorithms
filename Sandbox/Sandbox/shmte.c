
#include <sys/fcntl.h>
#include <sys/mman.h>

int main (void) 
{
    int k = shm_open("/abc/shmem", O_RDWR);
}

