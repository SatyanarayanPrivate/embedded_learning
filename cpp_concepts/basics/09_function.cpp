#include <iostream>
using namespace std;


namespace FunctionBasics {
/*
1.naming convention
2.return type
3.calling convention
4.name
5.arguement
6.exception list
7.prolog
8.Body
9.epilog
*/
/*extern "C" void __stdcall fun(int x, int y) throw(int,float) 
{ // prolog
  //function body
} // epilog
*/
int fun(void) {
    /* -------- prolog -----------
    push    ebp        //save callers frame base pointer
    mov    ebp, esp    //set current base pointer
    sub    esp, 192   //allocate memory for local variables
    */
    
    /* -------- body ----------- */
    
    /* --------- epilog ----------
    mov    esp, ebp    //remove local variables    
    pop    ebp            //reset base pointer
    ret    0            //return to caller
    */    
}
int main (void) {
    fun();
    /*
    *    push    20  
    *    push    10
    *    call    ?fun@@YAXHH@Z                
    *    add    esp, 8    //remove arguments from the stack
    */
    return 0;    
}
}

namespace FunctionOverloading {
    void fun () { cout << "fun " << endl; }
    void fun (int val) { cout << "fun int " << endl; }
    void fun (char val) { cout << "fun char " << endl; }
    void fun (double val) { cout << "fun double " << endl; }
    int fun (long val) { cout << "fun long " << endl; }
    /* //ambiguating new declairation
    void fun (long val) { cout << "fun long " << endl; }*/    
    int main (void) {
        using namespace FunctionOverloading;
        
        fun ();
        fun ('q');
        fun ((int) (10));
        fun ((long) (10));
        return 0;
    }
}

namespace FunctionNamingConventions {
namespace Ex3 {
    void fun()  {}
    void fun(int i) {}
    extern "C" void fun1() /*_fun1*/{}
    //extern "C" void fun1(int ) {}   /*conflicting declairation*/
    extern "C++" void fun2() {}
    namespace n1 {
        void fun() {}
    }
    class CA {
    public:
        static void fun()    {    }
    };
}
using namespace Ex3;
int main() {
    fun();      //call    ?fun@@YAXXZ                
    fun(10);    //call    ?fun@@YAXH@Z
    fun2();//call    ?fun2@@YAXXZ
    fun1();//call    _fun1
    n1::fun();  //call    ?fun@n1@@YAXXZ                
    CA::fun();  //call    ?fun@CA@@SAXXZ        
    return 0;
}
}

namespace FunctionTemplateFunction {
template<typename T>
T Add (T a,T b) {return a + b;}
int main (void) {
    Add (2, 4);
    Add (2.5, 4.8);
    Add (2, 4);
    return 0;
}
}


namespace FunctionCallingConventions {
#if 0
/*
 - if free size is know, then vendor should use __stdcall
 */
void __cdecl fun(int i,int j) { 
}//ret    0

void __stdcall fun2(int i,int j) {
}//ret    8

void __fastcall fun3(int i,int j) {
}//ret    0
class CA {
public:
    void __thiscall fun4(int i,int j) {
    }//ret    8
};
int main()
{
    CA obj;
    obj.fun4(10,20);
    /*
     * push    20                    
     * push    10                    
     * lea    ecx, DWORD PTR _obj$[ebp]
     * call    ?fun4@CA@@QAEXHH@Z            
     */
    fun(10,20);
    /*
     * push    20                    
     * push    10                    
     * call    ?fun@@YAXHH@Z                
     * add    esp, 8
     */
    fun2(10,20);
    /*
     * push    20                    
     * push    10                    
     * call    ?fun2@@YGXHH@Z                
     */
    fun3(10,20);
    /*
     * mov    edx, 20                    
     * mov    ecx, 10                    
     * call    ?fun3@@YIXHH@Z                
     */
    return 0;
}
#endif
}

namespace FunctionVirtual {
struct Emp {
    Emp(int data) {}
    virtual void dojob() { cout<<"employee dojob"<<endl; }
};
struct Manager: Emp {
    Manager():Emp(12){};
    virtual void dojob() { cout<<"manager dojob"<<endl; }
};
struct Tester : Emp {
    virtual void dojob() { cout<<"tester dojob"<<endl; }
};

int main (void) {
    Emp* emp = new Emp(12);
    emp->dojob();
    
    Emp* emp1 = new Manager();   // as it is refering vtable of base class
    emp1->dojob(); 
    return 0;
}
}