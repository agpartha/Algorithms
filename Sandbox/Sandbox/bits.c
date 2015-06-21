

int main (void)
{
        unsigned char gb = 0xdf;
        unsigned char mask = 0x01;
        unsigned char lc   = 0;
        unsigned char nb = 0;

        while (lc < 8) {
                nb = (nb << lc) | ((gb & mask) >> lc);
                lc++;
                mask = mask << 1;
                printf ("gb 0x%x lc %d mask 0x%x nb 0x%x\n", 
                        gb, lc, mask, nb);
        }
}

