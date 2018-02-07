#include <iostream>
#include <typeinfo>
using namespace std;

namespace RttiExample {
class Employee
{
public:
    void DoJob() {
        cout << "Employee Job" << endl;
    }
    virtual ~Employee() {
        cout << "Employee Dtor" << endl;
    }
};
class Manager :public Employee/*Is-A*/ {
public:
    void DoJob() {
        cout << "Employee Job" << endl;
    }
};
class Tester :public Employee {
public:
    void DoJob() {
        cout << "Employee Job" << endl;
    }
};

void Business(Employee & emp) {
    cout << "emp= " << typeid(emp).name() << endl;
    if (typeid(emp) == typeid(Manager))
        cout << "Apple" << endl;
    else
        cout << "Orange" << endl;
    
    cout << "Business started " << endl;
    emp.DoJob();
    cout << "Business completed " << endl;
    cout << "__________________________" << endl;
}

int main() {
    Manager man;
    Tester tester;
    Business(man);
    Business(tester);

    return 0;
}
}

namespace CallbackExample {
class CA {
    int x;
    int y;
public:
    CA(int x, int y) :x(x), y(y) {
        
    }
    void fun1() {
        cout << "Apple x=" << x << endl;
    }
    void fun2() {
        cout << "Orange y=" << y << endl;
    }
};

void VendorBusiness(CA & obj, void(CA::*pf)()) {
    cout << "Business Started ..." << endl;
    (obj.*pf)();//callback
    cout << "Business Completed ..." << endl;
    cout << "________________" << endl;
}

int main() {
    CA obj1(11, 22);
    CA obj2(111, 222);
    
    VendorBusiness(obj1, &CA::fun2);
    VendorBusiness(obj2, &CA::fun1);
    return 0;
}
}