#include <REGX52.H>

void Delay_ms(unsigned int time)
{
    unsigned int j;
    while (time--)
    {
        for (j = 0; j < 123; j++)
        {
				
				}
    }
}

int main()
{
    unsigned char i;
    P0 = 0x00;
	
    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            P0 = (P0 << 1) + 0x01;
            Delay_ms(500);
        }

        for (i = 0; i < 8; i++)
        {
            P0 = (P0 << 1);
            Delay_ms(500);
        }

        for (i = 0; i < 8; i++)
        {
            P0 = (P0 >> 1) + 0x80;
            Delay_ms(500);
        }

        for (i = 0; i < 8; i++)
        {
            P0 = (P0 >> 1);
            Delay_ms(500);
        }
    }
}
