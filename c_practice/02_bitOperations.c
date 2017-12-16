#include <stdio.h>


#define SET_BIT(num, position) (num | (0x01 << position))
#define CLEAR_BIT(num, position) (num & ~(0x01 << position))
#define TOGGLE_BIT(num, position) (num ^ (0x01 << position)) 


int main () {

    unsigned int val = 0x00;
    unsigned position = 0x00;

    val = 0x21;
    position = 0x1;
    printf ("Set_bit (%x, %d) = %x\n", val, position,  SET_BIT (val, position));
    position = 0x0;
    printf ("clear_bit (%x, %d) = %x\n", val, position,  CLEAR_BIT (val, position));
    position = 0x0;
    printf ("toggle_bit (%x, %d) = %x\n", val, position,  TOGGLE_BIT (val, position));

    return 0;
}
