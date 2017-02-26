/*
 *
 ******************************************************************************* 

   The MIT License (MIT)

   Copyright (c) <2015> <Anand Girish>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
 
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
 
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

 *******************************************************************************
 *
 */

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
