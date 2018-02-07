#include <iostream>
using namespace std;

class CA
{
    int x = 100;//c++11
    const int y = 200;
    int z = 300;
public:
    int a;
    int b;

    // order of initialization shoud be matched with order of declairation
    CA() :b(a), y(20), x(y), z(y), a(b)
    {
    }
    void Display()
    {
        cout << "x=" << x << endl;
        cout << "y=" << y << endl;
        cout << "z=" << z << endl;
        cout << "a=" << a << endl;
        cout << "b=" << b << endl;
    }
};

int main()
{
    CA obj;
    obj.Display();
    
    return 0;
}