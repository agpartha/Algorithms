
#include <stdio.h>

//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
    #define DEBUG printf
#else  /* DEBUG_PRINT */
    #define DEBUG(...) ((void)0) 
#endif /* DEBUG_PRINT */


int main (int argc, char **argv)
{
    unsigned int  octet = 0,ip_addr = 0;
    char *str_ip, str[256];

    str_ip = str;
    printf("Please provide IPV4 address in string format \n");
    scanf("%s", str_ip);
    printf("\nIP address: %s\n", str_ip);

    while (*str_ip) {
        octet = octet * 10 + (*str_ip - '0');
        DEBUG("str %c octet 0x%x\n", *str_ip, octet);
        str_ip++;

        // Terminating dot or end of the string 
        if ((*str_ip == '.') || (*str_ip == 0)) {
            DEBUG("ip_addr 0x%x\n", ip_addr);
            ip_addr =  (ip_addr << 8) | octet;
            DEBUG("ip_addr 0x%x\n", ip_addr);
            octet = 0x0;
            // only if dot move to next octet
            if (*str_ip)
                str_ip++;
        }
    }
    printf("\nIP Address Hex: 0x%x, network order 0x%x\n\n", ip_addr, htonl(ip_addr));

    //convert back to string and print it out.
    char re_str[256];
        
    if (ip_addr == 0x0) 
        str_ip = "0.0.0.0"; 
    else  {
        str_ip = re_str;

        str_ip += snprintf(str_ip, 5, "%d.", (ip_addr >> 24) & 0x000000FF);
        DEBUG("IP Address Re-Str %s\n", re_str);

        str_ip += snprintf(str_ip, 5, "%d.", (ip_addr >> 16) & 0x000000FF);
        DEBUG("IP Address Re-Str %s\n", re_str);

        str_ip += snprintf(str_ip, 5, "%d.", (ip_addr >> 8) & 0x000000FF);
        DEBUG("IP Address Re-Str %s\n", re_str);

        str_ip += snprintf(str_ip, 5, "%d", ip_addr & 0x000000FF );

        printf("IP Address Re-Str %s\n", re_str);
    }
}
