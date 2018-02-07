#include<iostream>
using namespace std;

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

int main1() {
    // allocate memory on heap
    CA *ptr = new CA();
    cout << "ptr= " << ptr << endl;

    // release memory
    delete ptr;
    return 0;
}

int main2() {
    // alloc array of object
    CA *ptr = new CA[5];
    cout << "______________________________" << endl;
    // release
    delete[] ptr;
    
    return 0;
}
int main3()
{
}

int main4()
{
    try
    {
        CA *ptr = new CA();
        if (ptr != NULL)
        {
            delete ptr;	// need to handle exceptions as new returns bad_alloc on error
        }
    }
    catch (bad_alloc & bad)
    {
        cout << bad.what() << endl;
    }

    // OR
    CA *ptr = new(nothrow) CA();
    if (ptr != NULL)
    {
        delete ptr;	// need to handle exceptions as new returns bad_alloc on error
    }
    return 0;
}

int main() {
    int *buffer = new int[255];
    cout << "buffer = " << buffer << endl;

    CA *ptr = new(buffer) CA();
    CA *ptr1 = new(buffer + 1) CA();
    CA *ptr2 = new(buffer + 5) CA();
    //dtor has to be called explicitly
    ptr->CA::~CA();
    ptr1->CA::~CA();
    ptr2->CA::~CA();

    delete[] buffer;
    return 0;
}