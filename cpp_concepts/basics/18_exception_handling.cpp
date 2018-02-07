#include<iostream>
using namespace std;


namespace Exception_Default_terminate_method {
void Release() {
    cout << "Resources released in Release fun" << endl;
    //exit(0);  //commented in linux
}
int main() {
    set_terminate(Release);     //register termiante method (from where you can free/ handle resources
    cout << "Resources alloted in main" << endl;
    throw 100;
    cout << "Resources released in main" << endl;

    return 0;
}
}

namespace Exception_Function {
void fun() {
    cout << "Apple " << endl;
    throw 100.89;
    cout << "Orange" << endl;
}

int main() {
    cout << "Pine" << endl;
    try {
        fun();
    }
    catch (int exp) {
        cout << "int exp =" << exp << endl;
    }
    catch (double d) {
        cout << "double exp=" << d << endl;
    }
    cout << "Jack" << endl;

    return 0;
}
}

namespace Exception_Handling_Flow {
class CA {
public:
    CA() {
        cout << "CA Ctor" << endl;
    }
    CA(CA & pp) {
        cout << "CA Copy" << endl;
    }
    ~CA() {
        cout << "CA D-tor" << endl;
    }
};
void fun1() {
    cout << "Apple " << endl;
    throw 100.89;
    cout << "Orange" << endl;
}
int main() {
    cout << "Pine" << endl;
    /*
    creates catch table per try block
    - thrown information copied to catch table
    - local variable gets released
    - exception copied to catch block
    */
    try {
        CA obj1;
        throw obj1;
        fun1();
    }
    catch (int & exp) {
        cout << "int exp= " << exp << endl;
    }
    catch (double d) {
        cout << "Outer double exp=" << d << endl;
    }
    catch (CA obj) {
        cout << "CA exp=" << endl;
    }
    cout << "Jack" << endl;

    return 0;
}
}

namespace Exception_Concept_01 {
class CA {
public:
    CA() {
        cout << "CA Ctor" << endl;
    }
    CA(CA & pp) {
        cout << "CA Copy" << endl;
    }
    ~CA() {
        cout << "CA D-tor" << endl;
        throw 100;  // never throw exceptions from Dtor
        // exception overlaping can not be handled
    }
};
void fun1() {
    cout << "Apple " << endl;
    throw 100.89;
    cout << "Orange" << endl;
}
int main() {
    cout << "Pine" << endl;
    try {
        CA obj1;
        throw obj1;
        fun1();
    }
    catch (int & exp) {
        cout << "int exp= " << exp << endl;
    }
    catch (double d) {
        cout << "Outer double exp=" << d << endl;
    }
    catch (CA obj) {
        cout << "CA exp=" << endl;
    }
    cout << "Jack" << endl;

    return 0;
}
}

namespace Exception_Concept_02 {
int main() {
    cout << "Pine" << endl;
    try {
        try {
            throw 10;
            //throw "string";
        }
        catch (double d)  {
            cout << "Outer double exp=" << d << endl;
        }
        catch (int & exp) {
            exp += 101; // updates catch table
            cout << "Outer int exp=" << exp << endl;
            throw;//rethrow
        }
        catch (...) {//catch any / catch all / general exp
            cout << "Outer general exp=" << endl;// << exp << endl;
            throw 300;
        }
    }
    catch (int par) {
        cout << "Inner int exp=" << par << endl;
    }
    cout << "Jack" << endl;

    return 0;
}
}


class CAT {
public:
    CAT() {
        cout << "CAT Ctor" << endl;
        throw 100;  // this will avoid memory leaks, if new fails
    }

    ~CAT() {
        cout << "CAT D-tor" << endl;
    }
};


int main() {
    CAT *catPtr = NULL;
    try
    {
        catPtr = new CAT();
        /*
            CA *temp=operator new(size){}
            try {
                temp->CAT::CAT();
            }
            catch(...) {
                free(temp);
                throw;
            }
            catPtr=temp;
        */

        /*
         *
         *			push	1
         *			call	??2@YAPAXI@Z				; operator new
         *			add	esp, 4
         *
         *			mov	DWORD PTR tv129[ebp], eax
         *			mov	eax, DWORD PTR tv129[ebp]
         *			mov	DWORD PTR $T3[ebp], eax
         *			mov	BYTE PTR __$EHRec$[ebp+12], 1
         *			cmp	DWORD PTR $T3[ebp], 0
         *			je	SHORT $LN6@main
         *			mov	ecx, DWORD PTR $T3[ebp]
         *			call	??0CAT@@QAE@XZ				; CAT::CAT
         *			mov	DWORD PTR tv132[ebp], eax
         *			mov	ecx, DWORD PTR tv132[ebp]
         *			mov	DWORD PTR tv71[ebp], ecx
         *			jmp	SHORT $LN7@main
         *			$LN6@main:
         *			mov	DWORD PTR tv71[ebp], 0
         *			$LN7@main:
         *			mov	edx, DWORD PTR tv71[ebp]
         *			mov	DWORD PTR $T2[ebp], edx
         *			mov	BYTE PTR __$EHRec$[ebp+12], 0
         *			mov	eax, DWORD PTR $T2[ebp]
         *			mov	DWORD PTR _catPtr$[ebp], eax
         *
         */
    }
    catch (int exp) {
        cout << "int exp=" << exp << endl;
    }

    if (catPtr == NULL) {
        cout << "Apple" << endl;
    }
    else {
        cout << "Orange" << endl;
        delete catPtr;
    }

    return 0;
}
