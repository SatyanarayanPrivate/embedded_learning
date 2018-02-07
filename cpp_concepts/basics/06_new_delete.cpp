#include <iostream>
using namespace std;

/*
// New types
- normal new
- nothrow new
- placement new
- overloaded new
*/

namespace NewDeleteConpcept01 {
class CA
{
public:
    CA()
    {
        cout << "Default" << endl;
    }
    ~CA()
    {
        cout << "D-tor " << endl;
        delete this;    // recursive call to Dtor till stack overflow
        /*
        call dtor
        free()
        */
    }
};

int main()
{
    CA *obj5 = new CA();
    /*
    1) allot memory(malloc)
    2) call ctor
    */

    delete obj5;
    /*
    call dtor
    free()
    */
    
    return 0;
}
}

namespace NewDeleteGlobalOverloading {
#if 0
//Overloading global new & delete
void* operator new(size_t sz) {
    void* m = malloc(sz);
    if(!m)
    cout<<"out of memory"<<endl;
    return m;
}
void operator delete(void* m) {
    free(m);
}
int main() {
    int* p = new int(47);
    delete p;
    CA* pobj = new CA;
    delete pobj;
    CA* obj = new CA[3];
    delete []obj;
}
#endif
}

namespace NewDeleteClass {
// Overloading new & delete for a class and array
class CA
{
public:
    CA()
    {
        cout << "CA Default Ctor= " << this << endl;
    }
    ~CA() {
        cout << "Dtor CA= " << this << endl;
    }
    // The static keyword is optional for new & delete operators. when you overload new and delete for a class, you’re creating static member functions.
    void * operator new( size_t cb ) {
        return malloc(cb);
    }
    static void operator delete(void * obj) {
        free(obj);
    }
    void * operator new[](size_t cb ) {
        cout<<"n[]"<<endl;
        return ::new char[cb];
    }

    void operator delete[](void * obj) {
        cout<<"d[]"<<endl;
        ::delete []obj;
    }
};
int main() {
    CA *obj = new CA;
    delete obj;
    CA *obj1 = new CA[10];
    delete []obj1;
    
    return 0x00;
}
}

namespace NewDeleteTypes {
class CA
{
public:
    CA()
    {
        cout << "CA Default Ctor= " << this << endl;
    }
    ~CA() {
        cout << "Dtor CA= " << this << endl;
    }
};

int main () {
    // allocate object of class
    CA *ptr = new CA();
    cout << "ptr= " << ptr << endl;
    // release memory
    delete ptr;

    // alloc array of object
    CA *ptr1 = new CA[5];
    cout << "______________________________" << endl;
    // release
    delete []ptr1;

    // incorrect way
    CA *ptr2 = new CA();
    if (ptr2 != NULL) {
        delete ptr2;    // need to handle exceptions as new returns bad_alloc on error
    }
    
    try {
        CA *ptr3 = new CA();
        if (ptr3 != NULL) {
            delete ptr3;	// need to handle exceptions as new returns bad_alloc on error
        }
    }
    catch (bad_alloc & bad) {
        cout << bad.what() << endl;
    }
    // OR
    CA *ptr4 = new(nothrow) CA();
    if (ptr4 != NULL) {
        delete ptr4;	// need to handle exceptions as new returns bad_alloc on error
    }

    //placement new
    int *buffer = new int[255];
    cout << "buffer = " << buffer << endl;

    CA *ptr_ = new(buffer) CA();        //placement new
    CA *ptr1_ = new(buffer + 1) CA();
    CA *ptr2_ = new(buffer + 5) CA();
    //dtor has to be called explicitly
    ptr_->CA::~CA();
    ptr1_->CA::~CA();
    ptr2_->CA::~CA();

    delete[] buffer;

    return 0;
}
}

class CA
{
    bool IsOnHeap;
    static bool GlobalHeap;
    static int GlobalCount;
public:
    CA() :IsOnHeap(GlobalHeap)
    {
        GlobalCount--;
        if (GlobalCount <= 0)
            GlobalHeap = false;
    }
    static void * operator new(size_t size)
    {
        void *pt = malloc(size);
        GlobalHeap = true;
        //((CA*)pt)->IsOnHeap = true;
        return pt;
    }
    static void * operator new[](size_t size)
    {
        void *pt = malloc(size);
        GlobalHeap = true;
        GlobalCount = size / sizeof(CA);
        //((CA*)pt)->IsOnHeap = true;
        return pt;
    }
    void ObjectLocation()
    {
        if (IsOnHeap == true)
        {
            cout << "Object is on heap " << endl;
        }
        else
        {
            cout << "Object is (not) on heap " << endl;
        }
    }
};
bool CA::GlobalHeap = false;
int CA::GlobalCount = 0;

int main()
{
    CA obj1;
    CA *ptr1 = new CA();
    CA *ptr2 = new CA();
    /*
     * push	1
     * call	??2CA@@SAPAXI@Z				; CA::operator new
     * add	esp, 4
     * 
     * 
     * call	??0CA@@QAE@XZ				; CA::CA
     * 
     * 
     */
    CA obj2;
    obj1.ObjectLocation();
    obj2.ObjectLocation();
    ptr1->ObjectLocation();
    ptr2->ObjectLocation();
    
    cout << "______________________________" << endl;
    CA *ptr = new CA[5];
    /*
     * 
     */
    for (size_t i = 0; i < 5; i++)
    {
        (ptr + i)->ObjectLocation();
    }
    return 0;
}