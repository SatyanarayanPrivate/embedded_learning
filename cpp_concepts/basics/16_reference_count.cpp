#include <iostream>
#include <map>
using namespace std;

class SmartPointer;
class CA {
    int *i;
    
    CA (): i (new int(100)) {
        cout << "CA ctor" << endl;
    }
    CA (CA & ObjRef): i(ObjRef.i) {
    }
    CA & operator = (CA & ObjRef) {
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
    void FunctionCA () {
        cout << "FunctionCA !!!!" << endl;
    }    
    friend class SmartPointer;
};

class SmartPointer {
    CA *CaPtr;
    static map<CA*, int> MyMap;
    void * operator new (size_t Size) {
        return NULL;
    }
    void * operator new [] (size_t Size) {
        return NULL;
    }
    void operator delete (void *ptr) {
    }
    void operator delete [] (void *ptr) {
    }
public:
    SmartPointer (): CaPtr (CA:: CreateCA()) {
        MyMap[CaPtr] = 1;
    }
    SmartPointer (SmartPointer & ObjRef): CaPtr (ObjRef.CaPtr) {
        int count = MyMap [CaPtr];
        MyMap [CaPtr] = count + 1;
    }
    ~SmartPointer () {
        int count = MyMap [CaPtr] - 1;
        if (count == 0x00) {
            delete CaPtr;
            MyMap.erase (CaPtr);
        }
        else {
            MyMap [CaPtr] = count;
        }
    }
    SmartPointer & operator = (SmartPointer & ObjRef) {
        if (CaPtr != ObjRef.CaPtr) {
            //this->SmartPointer::~SmartPointer();        // linux compiler error
            //this->SmartPointer::SmartPointer(ObjRef);   // linux compiler error
        }
    }
};

map<CA*, int> SmartPointer:: MyMap;

int main () {
    SmartPointer smt;
    
    return 0;
}