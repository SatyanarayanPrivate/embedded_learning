#include<iostream>
using namespace std;


// namespace:: avoid potential naming clashing

namespace sachin
{
    int i = 10;
    int j = 120;
}
void main1()
{
    cout << sachin::i << endl;	// selective usage
}
void main2()
{
    using sachin::i;	// selective exposure
    cout << i << endl;
}
void main3()
{
    using namespace sachin;	// full exposure
    cout << i << endl;
    cout << j << endl;
}

// nested
namespace saurav {
    using namespace sachin;
    int x = 100;
    int y = 200;
}

namespace rahul {
    int i = 222;
    int j = 333;
    namespace dravid {	// nested namespace
        int x = 444;
        int y = 555;
    }
}
// namespace concantination
namespace sehwag {
    int i = 123;
    int j = 3423;
}
namespace sehwag { // gets merged but chance of clashing if same name
    int x = 999;
    int y = 777;
}

void main4() {
    {
        using namespace saurav;
        cout << i << endl;
        cout << j << endl;
    }
    {
        using namespace rahul;
        using namespace rahul::dravid; // need to mention explicitly
        cout << i << endl;
        cout << j << endl;
        cout << x << endl;
        cout << y << endl;
    }
    {
        using namespace sehwag;
        cout << i << endl;
        cout << j << endl;
        cout << x << endl;
        cout << y << endl;
    }
}

#if 0
namespace {
int i= 200;
}
namespace {
//int i= 200;     //redefination error
int j= 200;
}
//int i;  // error: reference to ‘i’ is ambiguous
int main() {
cout<<i<<endl;
return 0;
}
#endif