#include<iostream>
using namespace std;


class CA_1
{
public:
    void fun() {
        cout << "this= " << this << endl;
    }
    void fun1() {
        cout << "fun1" << endl;
    }
    void fun2() {
        cout << "fun2" << endl;
    }
    void fun3() {
        cout << "fun3" << endl;
    }
    
};
class CA_2
{
public:
    virtual void fun1() {
        cout << "fun1" << endl;
    }
    virtual void fun2() {
        cout << "fun2" << endl;
    }
    void fun3() {
        cout << "fun3" << endl;
    }
    
};
void main1()
{
    /*
     *   cout << "sizeof=" << sizeof(CA_1) << endl;
     * 
     *   CA_1 obj;
     *   cout << "&obj = " << &obj << endl;
     *   obj.fun();
     */
    cout << "sizeof=" << sizeof(CA_2) << endl;
    
    CA_2 obj;
    ((void(*)())*(long*)*(long *)&obj)();
    // step 1 reach the vptr
    long *vp = (long*)&obj;
    // step 2 reach the vtable
    // vtable in data segment
    long *vt = (long*)*vp;
    // step 3 reach function 
    //typedef void(*FPTR)();
    using FPTR = void(*)(); //c++11
    FPTR fp = (FPTR)vt[1];
    // step 4 call function
    fp();
}

class CA
{
public:
    virtual void fun1() {
        cout << "\t\t\tfun1 CA" << endl;
    }
    virtual void fun2() {
        cout << "\t\t\tfun2 CA" << endl;
    }
    void fun3() {
        cout << "\t\t\tfun3 CA" << endl;
    }
    
};

class CB : public CA
{
public:
    virtual void fun2() // overriding
    {
        cout << "\t\t\tfun2 CB" << endl;
    }
    virtual void fun4() {
        cout << "\t\t\tfun3 CB" << endl;
    }
    
};
int main() {
    CA obj1;
    long *vp1 = (long*)&obj1;
    cout << "CA::vftable = " << *vp1 << endl;
    ((void(*)())(((long *)*vp1)[0]))();
    ((void(*)())(((long *)*vp1)[1]))();
    CB obj2;
    long *vp2 = (long*)&obj2;
    cout << "CB::vftable = " << *vp2 << endl;
    ((void(*)())(((long *)*vp2)[0]))();
    ((void(*)())(((long *)*vp2)[1]))();
    ((void(*)())(((long *)*vp2)[2]))();
    
    return 0;
}

int main2()
{
    CA obj;
    CA &objref = obj;
    CA *objptr = &obj;
    
    // using object, refernce and pointer, non virtual fun are directly resolved from code.
    // using refernce and pointer, virtual fun are directly resolved via vtable.
    
    // both directly resolved from code segment
    obj.fun1();
    obj.fun3();
    
    // resolved via vtable
    objref.fun1();
    // directly resolved from code segment
    objref.fun3();
    
    // resolved via vtable
    objptr->fun1();
    // directly resolved from code segment
    objptr->fun3();
    
    return 0;
}