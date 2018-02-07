#include <iostream>
using namespace std;

class SmartPointer;
class CA {
    int *i;
    CA (): i(new int(100)) {
        cout << "CA Ctor" << endl;
    }
    ~CA () {
        cout << "CA Dtor" << endl;
        delete i;
    }
    CA& operator = (CA &ObjRef) {
        i = ObjRef.i;
        return *this;
    }
    
    static CA* CreateCA () {
        return new CA();
    }
    static void ReleaseCA (CA *ptr) {
        delete ptr;
    }
public: 
    void FunCA (void) {
        cout << "FunCA ..." << endl;
    }
    
    friend class SmartPointer;
};

class SmartPointer {
    CA *CaPtr;
    
    void* operator new (size_t Size) {
        return NULL;
    }
    void* operator new [] (size_t Size) {
        return NULL;
    }
    void operator delete (void *ptr) {
    }
    void operator delete [] (void *ptr) {
    }
public:
    SmartPointer (): CaPtr (CA::CreateCA()) {
    }
    SmartPointer (SmartPointer & ObjRef): CaPtr (ObjRef.CaPtr) {
        ObjRef.CaPtr = NULL;
    }
    ~SmartPointer () {
        CA:: ReleaseCA (CaPtr);
    }
    SmartPointer & operator = (SmartPointer & ObjRef) {
        if (CaPtr != NULL) {
            delete CaPtr;
        }
        CaPtr = ObjRef.CaPtr;
        ObjRef.CaPtr = NULL;
        return *this;
    }
    
    CA* operator -> () {
        return CaPtr;
    }
};


int main (void) {
    SmartPointer smt;
        
    SmartPointer smt1;
    smt1 = smt;
    
    return 0;
}