#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


int main (int argc, char **argv)
{

    const char *cmd_line = "root=ramfs rw sysboot imgdev=/dev/mtd10 console=ttyS0,9600 post=0x00011800 card_index=0x2b03 card_rev=0x0002 ubootver=1.12 sysmgr_cmdline=-RSto autoboot lock_bootflash ubootlog=0xfffcf5c";
    char cmd_line_buf[300];
    const char *card_str  = "card_index=";
    char       *p_str, *p_space;
    unsigned   int  card_index, read_size;
    FILE *fp;

    
    fp = fopen ("./tmp", "r");
    if (fp == NULL) {
        printf("Could not open the file for read\n");
        exit (1);
    }
    
    read_size = fread(cmd_line_buf, 1, sizeof(cmd_line_buf), fp);
    printf("Read %d bytes from the file, Buf max %d\n", read_size, sizeof(cmd_line_buf));

    p_str = strstr(cmd_line_buf, card_str);
    if (p_str) {
        printf("Found Card string: %s, of length %d\n", p_str, strlen(p_str));
        p_str+= strlen(card_str);
        card_index = strtoul(p_str, &p_space, 16);
        printf("Card Index: %s, of value 0x%x\n", p_str, card_index);
    } else {
        printf("No Card string found:\n"); 
    }
}
