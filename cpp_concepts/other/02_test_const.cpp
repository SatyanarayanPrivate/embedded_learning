#include<iostream>
using namespace std;
namespace nm10
{
    void main()
    {
        int x = 10;
        int y = 20;
        
        //int *ptr = &x;//pointer
        //const int *ptr = &x;//pointer to a constant
        //int const *ptr = &x;//pointer to a constant
        //int  * const ptr = &x;//constant pointer
        int const * const ptr = &x;//constant pointer to a constant
        //*ptr=100;//l1
        //ptr=&y;//l2
        cout << "x=" << x << endl;
        cout << "y=" << y << endl;
        
    }
}