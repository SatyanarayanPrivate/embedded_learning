#include <iostream>
using namespace std;

// interface:: class includes only pure functions
// abstract class:: pure function with other methods

class CA {
public:
    int iInstance;
    const int iConst; 
    static int iStatic;
    mutable int iMutable;
    const static int iConstStatic;
    
    CA(): iInstance(100), iConst(200), iMutable(400)
    {
        //iConst = 23;    // compiler error: accessing read only member
    }    
    void ChangeState () const {
        //         iConst = 29;  // compiler error: accessing read only member
        iStatic = 302;
        iMutable = 401;
        //iConstStatic = 501; // compiler error: accessing read only member
    }
    void DisplayState () const {
        cout << "\niConst = " << iConst << endl; 
        cout << "iMutable = " << iMutable << endl;
        cout << "--------------------------------------------------- " << endl; 
    }
    
    static void DisplayShared () {
        //cout << "iMutable = " << iMutable << endl; //compiler error: invalid use of member
        cout << "iStatic = " << iStatic << endl; 
        cout << "iConstStatic = " << iConstStatic << endl; 
        cout << "--------------------------------------------------- " << endl; 
    }
};

//if not initiazed compiler error:: undefined reference to `CA::iStatic' be generated
int CA::iStatic = 300;
//int CA::iStatic = 304; // compiler error:: redefinition
const int CA:: iConstStatic = 500;


int main() {
    //int CA::iStatic = 300;  //compiler error: as static variables must initiazed at global scope
    int var;
    int *ptr = NULL;
    CA obj;
    
    /*Const member*/
    //obj.iConst = 10;      // compiler error: modifying read only member
    var = obj.iConst;
    //ptr = &obj.iConst;
    //*ptr = 101;             // compiler error: invalid conversion from ‘const int*’ to ‘int*’
    ptr = (int *)&obj.iConst; // forcefully modifying
    *ptr = 102;
    
    obj.iStatic = 301; // static varible can be accessed outside class
    CA::iStatic = 303;
    obj.iMutable = 401;
    
    var = obj.iConstStatic;
    obj.ChangeState ();
    obj.DisplayState();    
    obj.DisplayShared ();
    
    const CA obj1;
    //     obj1.iInstance = 10; // compiler error
    obj1.iStatic = 20; 
    obj1.iMutable = 30; 
    
    obj1.DisplayState();    
    obj1.DisplayShared ();
}
