//kate: auto-brackets: true

#include <iostream>
using namespace std;

/*
//method types while inheritance
- hidding 
- uppending 
- overriding
- overloading
*/

namespace InheritanceConcept01 {
/*
--------------------------------------------------------------
Inheritance     |    Base Class       |   Derived Class      |
----------------|---------------------|----------------------|
    Public      |        Public       |       Public         |
                |        Protected    |       Protected      |
                |        Private      |       Not Access     |
----------------|---------------------|----------------------|                       
    Protected   |        Public       |       Protected      |
                |        Protected    |       Protected      |
                |        Private      |       Not Access     |
----------------|---------------------|----------------------|   
    Private     |        Public       |       Private        |
                |        Protected    |       Private        |
                |        Private      |       Not Access     |
--------------------------------------------------------------   
*/
class CA {
    int x;
protected: 
    int y;
public: 
    int z;
    CA (): x(100), y(200), z(300) {
    }
    void Display() {
        cout << "\nDispCA !!!" << endl;
        cout << "x=" << x << endl;
        cout << "y=" << y << endl;
        cout << "z=" << z << endl;
        cout << "-----------------------------------------------" << endl;
    }    
};

class CB: public CA {
public:
    void Display() {
        cout << "\nDispCB !!!" << endl;
        //cout << "x=" << x << endl;    // x is private member of base class, which is inaccessable
        cout << "y=" << y << endl;      // protected become protected in derived class
        cout << "z=" << z << endl;      // public become public in derived class
        cout << "-----------------------------------------------" << endl;
    }        
};
class CB_1: public CB {
public:
    void Display() {
        cout << "\nDispCB_1 !!!" << endl;
        //cout << "x=" << x << endl;    // x is private member of base class, which is inaccessable
        cout << "y=" << y << endl;      // protected become protected in derived class
        cout << "z=" << z << endl;      // public become public in derived class
        cout << "-----------------------------------------------" << endl;
    }        
};

class CC: protected CA {
public:
    void Display() {
        cout << "\nDispCC !!!" << endl;
        //cout << "x=" << x << endl;    // x is private member of base class
        cout << "y=" << y << endl;      // protected become protected in derived class
        cout << "z=" << z << endl;      // public become in protected derived class
        cout << "-----------------------------------------------" << endl;
    }        
};

class CC_1: public CC {
public:
    void Display() {
        cout << "\nDispCC_1 !!!" << endl;
        //cout << "x=" << x << endl;    // x is private member of base class
        cout << "y=" << y << endl;      // protected become in derived class
        cout << "z=" << z << endl;      // public become in derived class
        cout << "-----------------------------------------------" << endl;
    }        
};


class CD : private CA
{
    void Display() {
        cout << "\nDispCD !!!" << endl;
        //cout << "x=" << x << endl;    // x is private member of base class
        cout << "y=" << y << endl;
        cout << "z=" << z << endl;
        cout << "-----------------------------------------------" << endl;
    }        
};

int main () {
    CA objA;
    //objA.x = 101; //private state
    //objA.y = 201; //protected state
    objA.z = 301;
    objA.Display();
    
    CB objB;
    //objB.x = 101; //private state of base class 
    //objB.y = 201; //protected state of base class
    objB.z = 301;
    objB.Display();
    CB_1 objB1;
    //objB1.x = 101; //private state of base class 
    //objB1.y = 201; //protected state of base class
    objB1.z = 301;
    objB1.Display();
    
    CC objC;
    //objC.x = 101;   //private state of base class 
    //objC.y = 201;   //protected state of base class 
    //objC.z = 301;   //inaccessable to derived class CC
    objC.Display();
    CC_1 objC1;
    //objC1.x = 101;   //private state of base class 
    //objC1.y = 201;   //protected state of base class 
    //objC1.z = 301;   //inaccessable to derived class CC
    objC1.Display();
    
    return 0;
}
}

namespace InheritanceChangeAccessControl {
class CA {
    int x;
protected: 
    int y;
public: 
    int z;
    CA (): x(100), y(200), z(300) {
    }
    void Display() {
        cout << "\nDispCA !!!" << endl;
        cout << "x=" << x << endl;
        cout << "y=" << y << endl;
        cout << "z=" << z << endl;
        cout << "-----------------------------------------------" << endl;
    }    
};

class CD : private CA
{
protected:
    //using CA::x;  //error x is private member
    CA::z;	// using is optional
    
public:
    // vertical access control
    // changing access of base in derived class
    using CA::y;
    using CA::Display;
    // friend function is horizontal access control
    void DisplayCD()
    {
        cout << "DispCD !!!" << endl;
        //cout << "x=" << x << endl;	// private member are not visible to derived class
        cout << "y=" << y << endl;		// protected member are visible to derived class
        cout << "z=" << z << endl;
        cout << "-----------------------------------------------" << endl;
    }
};

int main () {
    
    CD objD;
    //objD.x = 101;   //private state of base class 
    //objD.z = 301;   //inaccessable to derived class CC
    objD.y = 201;   //protected state of base class 
    objD.Display();
    objD.DisplayCD();
    
    return 0;
}
}

namespace InheritanceTypesOfMethods {
class CA {
private:// guard code
        int x;
protected:
    int y;
public:
    int z;
    CA() : CA(10, 20, 12)	// ctor delegation c++11
    {
        cout << "CA Default Ctor" << endl;
    }
    
    CA(int x, int y, int z) : x(x), y(y), z(z)
    {
        cout << "CA Param" << endl;
    }
    
    void DisplayCA()
    {
        cout << "DispCA !!!" << endl;
        cout << "x=" << x << endl;
        cout << "y=" << y << endl;
        cout << "z=" << z << endl;
        cout << "-----------------------------------------------" << endl;
    }
    
    void fun() {
        cout << "apple CA" << endl;
    }
    void fun1() {
        cout << "orange CA" << endl;
    }
    
    ~CA() {
        cout << "Dtor CA" << endl;
    }
};

class CB : public CA {
public:
    CA ca_obj;
    CB()
    { // prolog:: call CA::CA()
        cout << "CB Default Ctor" << endl;
    }
    // function hidding:: base class fun are hidden
    void fun() {
        cout << "apple CB" << endl;
    }
    // function uppending
    void fun2() {
        cout << "orange CB" << endl;
    }
    ~CB() {
        cout << "Dtor CB" << endl;
    }// epilog:: CA::~CA()
};

int main() {
    
    CB obj1;
    obj1.DisplayCA();
    obj1.fun();
    obj1.fun1();
    
    return 0;
}
}