#include<iostream>
using namespace std;

class CA
{
    int x = 10;	// c++11
    int y = 12;
public:
    CA()
    {

    }
    friend class Container;	// to grand permission of private members to class Container
    friend class CB;
};

//containment
class Container
{
    CA obj;
public:
    void fun()
    {
        cout << obj.x << endl;
        cout << obj.y << endl;
    }
};

class CB : CA
{
public:
    void fun()
    {
        cout << x << endl;
        cout << y << endl;
    }
};

class wrapper
{
    int k = 700;
    void outerfun() {
        cout << "fun outer" << endl;
    }
public:
    class inner
    {
        int h = 0;
        wrapper *wrap;
    public:
        inner(wrapper *wr) : wrap(wr)
        {
        }
        void fun()
        {
            wrap->outerfun();		// able to access outer class private member, bcz these are implicit friend
            cout << "fun inner" << endl;
        }
    };
};

class CV : public wrapper::inner
{
public:
    CV():inner(new wrapper())
    {

    }
};

int main1() {
    Container cnter;
    cnter.fun();
    
    return 0;
}

int main() {
    CV obj;
    obj.fun();    
    return 0;
}