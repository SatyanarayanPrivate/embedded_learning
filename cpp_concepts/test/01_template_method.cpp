#include <iostream>
using namespace std;

class Bank {
public:
    void DoJob () {
        cout << "Open DB operation" << endl;
        DoDelayedJob ();
        cout << "Close DB operation" << endl;
    }
protected:
    virtual void DoDelayedJob () = 0;
};

class SAccount: public Bank {
protected: 
    void DoDelayedJob () {
        cout << "Saving Account Operations" << endl;
    }
};

class CAccount: public Bank {
protected: 
    void DoDelayedJob () {
        cout << "Current Account Operations" << endl;
    }
};

int main (void) {
    SAccount Sobj;
    Sobj.DoJob();
    cout << "-----------------------------------------" << endl;
    CAccount Cobj;
    Cobj.DoJob();
    cout << "-----------------------------------------" << endl;
    return 0;
}