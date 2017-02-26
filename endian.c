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


/*
#include <arpa/inet.h>
*/
#include <netinet/in.h>
#include <stdio.h>

typedef union {
    unsigned char   bytes[sizeof(unsigned short)];
    unsigned short  shorty;
    }un_short;
typedef union {
    unsigned char   bytes[sizeof(unsigned long)];
    unsigned long   longy;
    }un_long;
    
int main (int argc, char **argv)
{
    int       little_endian;
    char      *disp_name;
    char      *le_disp_name = "Little Endian";
    char      *be_disp_name = "Big Endian";
    unsigned  short mask;
    un_short  end_det;
    un_short  var_short;
    un_long   var_long;

    /*
     * Initialize the short and Long values to known constants.
     * Also display how the Data is displayed in the machine.
     */
#ifdef  HOST_STORE
    var_short.shorty = 0xABCD;
    var_long.longy   = 0xAABBCCDD;
#else   /* HOST_STORE */
    /*
     * Here we are storing the data as it would have appeared in 
     * Network Packet Header for these fields of one short and one long
     * variable.
     */
    var_short.bytes[0] = 0xAB;
    var_short.bytes[1] = 0xCD;
    var_long.bytes[0]  = 0xAA;
    var_long.bytes[1]  = 0xBB;
    var_long.bytes[2]  = 0xCC;
    var_long.bytes[3]  = 0xDD;
#endif  /* HOST_STORE */

    printf(    "\n\n"
               "Short       : 0x%x    \n"
               "Short Bytes : 0 - 0x%x, 1 - 0x%x\n"
               "Long        : 0x%x     \n"
               "Long Bytes  : 0 - 0x%x, 1 - 0x%x, 2 - 0x%x, 3 - 0x%x\n",
               var_short.shorty, var_short.bytes[0], var_short.bytes[1], 
               var_long.longy, var_long.bytes[0], var_long.bytes[1],
               var_long.bytes[2], var_long.bytes[3]);
    /*
     * Determine if the Machine is Big/Little Endian
     */
    end_det.shorty = 0x01;
    if (end_det.bytes[0] == 1) {
        little_endian = 1;
        disp_name     = le_disp_name;
    } else {
        little_endian = 0;
        disp_name     = be_disp_name;
    }

    /*
     * If the machine is Little Endian, We will see a difference in machine 
     * data and network ordered. Here in this section we must see data as 
     * seen on network.
     *
     * If The machine is Big Endian, hton/htonl should not alter data.
     * Same should be true for ntohs/ntohl. Just demonstrate the same 
     */
    printf("\n%s hton Version:: Short : 0x%x    Long : 0x%x\n", 
                        disp_name,
                        htons(var_short.shorty), htonl(var_long.longy));
    printf("\n%s ntoh Version:: Short : 0x%x    Long : 0x%x\n", 
                        disp_name,
                        ntohs(var_short.shorty), ntohl(var_long.longy));
    printf("\n%s Value 0x%x hton 0x%x ntoh 0x%x ntoh-hton 0x%x\n", 
                        disp_name,
                        var_short.shorty,
                        htons(var_short.shorty), 
                        ntohs(var_short.shorty), 
                        ntohs(htons(var_short.shorty)));
    printf("\n\n");


    /*
     *  Always set the 7th - 13th bit in 16 bits as seen in Big endian Format
     */
    mask = (~(~0 << 7) << (13 + 1 -7)); 
    printf("\nMask 0x%x for setting Bits 7 to 13 in short integer 0x%x\n", 
            mask, var_short.shorty);
    /*
     * Operate in One Endian mode. When storing back to register, use this 
     * again to make sure bytes are back in same order as it was in HW.
     */
    var_short.shorty = ntohs(htons(var_short.shorty) | mask);;
    printf ("\nMask 0x%x shorty 0x%x Bytes 0x%x 0x%x\n",
            mask, var_short.shorty, 
            var_short.bytes[0], var_short.bytes[1]);
    printf("\n\n");
}
