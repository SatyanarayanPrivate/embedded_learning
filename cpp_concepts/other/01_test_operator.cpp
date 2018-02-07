#include<iostream>
using namespace std;

namespace TestExample01 {
class Rect;
class Polar
{
    double angle;
    double dist;
public:
    Polar(double angle, double dist) :angle(angle), dist(dist)
    {
    }
    operator Rect();
};
class Rect
{
    double xCor;
    double yCor;
public:
    Rect(double xCor, double yCor) :xCor(xCor), yCor(yCor)
    {
    }
    Rect() :xCor(0.0), yCor(0.0)
    {
    }
    friend ostream & operator<<(ostream & os, Rect &rect)
    {
        os << "x=" << rect.xCor << " and y=" << rect.yCor << endl;
        return os;
    }
    operator Polar() {
        Polar temp(11.2, 11.3);
        return temp;
    }
};
Polar::operator Rect()
{
    Rect temp;// (10.0, 20.0);
    return temp;
}

int main()
{
    Polar polar(3.14 / 2.0, 15.0);
    Rect rect;
    rect = polar;
    polar = rect;
    cout << rect << endl;
    
    return 0;
}
}

class Rect;
class Polar
{
    double angle;
    double dist;
public:
    Polar(double angle, double dist) :angle(angle), dist(dist)
    {
    }
    operator Rect();
    
    Polar operator= (Rect& ObjRef) {
        Polar temp(10.2,11.2);
        cout << "Polar operator= "<< endl;
        return temp;
    }
};
class Rect
{
    double xCor;
    double yCor;
public:
    Rect(double xCor, double yCor) :xCor(xCor), yCor(yCor)
    {
    }
    Rect() :xCor(0.0), yCor(0.0)
    {
    }
    friend ostream & operator<<(ostream & os, Rect &rect)
    {
        os << "x=" << rect.xCor << " and y=" << rect.yCor << endl;
        return os;
    }
//     Rect operator= (Polar& ObjRef) {
//         Rect temp(10.2,11.2);
//         cout << "Rect operator= "<< endl;
//         return temp;
//     }
};
Polar::operator Rect()
{
    Rect temp;// (10.0, 20.0);
    cout << "Polar operator Rect()  "<< endl;
    return temp;
}

int main()
{
    Polar polar(3.14 / 2.0, 15.0);
    Rect rect;
    rect = polar;
    polar = rect;
    cout << rect << endl;
    
    return 0;
}