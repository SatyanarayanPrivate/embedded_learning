#include <iostream>
using namespace std;

class CComplex {
    double real;
    double imag;

public:
    CComplex() : real(0.0), imag(0.0)
    {

    }
    CComplex(double real, double imag) : real/*member*/(real/*parameter*/), imag(imag)
    {
        this->real = real;
    }
    friend ostream & DisplayComplex(ostream & os, CComplex & obj);
    // friend  function:: non member function we define inside class or outside class
    friend ostream & operator<<(ostream & os, CComplex & obj)
    {
        os << obj.real << (obj.imag >= 0.0 ? " + " : "") << obj.imag << "i" << endl;
        return os;
    }
    ostream & operator<<(ostream & os)
    {
        os << this->real << (this->imag >= 0.0 ? " + " : "") << this->imag << "i" << endl;
        return os;
    }

    CComplex AddCComplex(CComplex & obj) {
        return CComplex(this->real + obj.real, this->imag + obj.imag);
    }
    CComplex operator+(CComplex & obj)
    {
        return CComplex(this->real + obj.real, this->imag + obj.imag);
    }

    CComplex operator+(int val)
    {
        return CComplex(this->real, this->imag + val);
    }

    friend CComplex operator+(int val, CComplex & obj)
    {
        return CComplex(obj.real + val, obj.imag);
    }
};

ostream & DisplayComplex(ostream & os, CComplex & obj)
{
    os << obj.real << (obj.imag >= 0.0 ? " + " : "") << obj.imag << "i" << endl;
    return os;
}

int main()
{
    CComplex c1;
    DisplayComplex(cout, c1) << "tested DisplayComplex" << endl;
    operator<< (cout, c1) << "tested operatoroverloading_func" << endl;;
    cout << c1 << "tested operatoroverloading" << endl;
    cout << "-------------------------------------------" << endl;

    CComplex c2(12.34, 13.45);
    CComplex c3(15.44, -11.47);
    cout << c2;
    cout << c3;
    cout << "-------------------------------------------" << endl;

    CComplex c4 = c2.AddCComplex(c3);
    cout << c4;
    cout << "-------------------------------------------" << endl;

    CComplex c5 = c2 + c3;
    //CComplex c5 = c2.operator+(c3);
    cout << c5;
    cout << "-------------------------------------------" << endl;

    CComplex c6 = c2 + 10; // add 10 to imaginary part
    cout << c6;
    cout << "-------------------------------------------" << endl;
    CComplex c7 = 10 + c2; // add 10 to real part
    cout << c7;
    cout << "-------------------------------------------" << endl;
    
    c7 << cout;
    
    return 0;
}
void main3_1()
{
    int x = 10;
    int & ptr = x;//refrence

    cout << "  &x=" << &x << endl;
    //cout << " ptr=" << ptr << endl;
    cout << "&ptr=" << &ptr << endl;
    cout << "ptr=" << ptr << endl;
    cout << "   x=" << x << endl;
}