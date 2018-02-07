#include <iostream>
using namespace std;

class SmartPointer; //forword declairation
/*
 - all ctor of base class should be defined in private
 - objects are allocated through methods only.
 - which are accessible to Smart Pointer class.
 */
class CA {

    int *i;
    // 
    CA (): i (new int(100)) {
        cout << "CA Ctor" << endl;
    }
    CA (const CA& ObjRef): i(new int(*ObjRef.i)) {
        cout << "CA Copy Ctor" << endl;
    }
    CA& operator= (CA& ObjRef) {
        *i = *ObjRef.i;
        cout << "CA Operator= " << endl;
        return *this;
    }
    ~CA () {
        cout << "CA Dtor" << endl;
        delete i;
    }
    static CA* CreateCA (){
        return new CA ();
    }
    static void ReleaseCA (CA *ptr) {
        delete ptr;
    }
public:
    
    void funCA () {
        cout << "funCA i = "<< *i << endl;
    }
    friend class SmartPointer;
};

/*
// Smart Pointer 
- should be overloaded with new and delete operators in private.
- is container of base class.
*/
class SmartPointer {
    CA *CaPtr;
    
    void *operator new(size_t Size) {
        return NULL;
    }
    void operator delete (void *ca_ptr) {
    }
    void *operator new[] (size_t Size) {
        return NULL;
    }
    void operator delete[] (void *ca_ptr) {
    }
public:
    SmartPointer (): CaPtr (CA:: CreateCA()) {
    }
    ~SmartPointer () {
        CA:: ReleaseCA (CaPtr);
    }
    CA * operator -> () {
        return CaPtr;
    }
    SmartPointer& operator = (SmartPointer &ObjRef) {
        *CaPtr = *ObjRef.CaPtr;
        return *this;
    }
};

int main (void) {
    //CA obj;
    //CA *ptr = CA::CreateCA ();
    //CA:: ReleaseCA(ptr);
    
    SmartPointer smt;
    smt->funCA();
        
    SmartPointer smt1;
    SmartPointer smt2;
    smt1 = smt2;
    
    return 0;
}