#include <stdio.h>


unsigned char isNumPowerOf(int a_num, unsigned int powerOf) {
    int num = a_num;    

    while (num != powerOf) {
        if ((num % powerOf) == 0x00) {
            num = (num / powerOf) + (num % powerOf);
        }
        else {
            break;
        }
    }
    if (num == powerOf) {
        printf ("%d is power of %d\n", a_num, powerOf); 
    }
    else {
        printf ("%d is not power of %d\n", a_num, powerOf); 
    }
}


int main (int argc, char *argv[]) {

    isNumPowerOf (5, 2);
    isNumPowerOf (6, 2);
    isNumPowerOf (4, 2);
    isNumPowerOf (16, 2);
    isNumPowerOf (9, 3);
    isNumPowerOf (12, 3);
    return 0;
}
