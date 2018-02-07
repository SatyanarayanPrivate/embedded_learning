#include<iostream>
#include <typeinfo>
using namespace std;

class StackBase
{
protected:
    StackBase() :top(-1)
    {
    }
    int top;
public:
    bool IsFull(){ return top == 4; }
    bool IsEmpty(){ return top == -1; }
};

template<typename T>
class Stack :public StackBase
{

    T arr[5];
public:
    Stack()
    {
        cout << "Stack generated for (" << typeid(T).name() << ")" << endl;
    }
    void Push(T val){ arr[++top] = val; }
    T Pop(){ return arr[top--]; }
    T Peek(){ return arr[top]; }

};
//FullSpecialization
template<>
class Stack<int> :public StackBase
{

    int arr[5];
public:
    Stack()
    {
        cout << "Stack generated for (Special for integer)" << endl;
    }
    void Push(int val){ arr[++top] = val; }
    int Pop(){ return arr[top--]; }
    int Peek(){ return arr[top]; }

};
template<>
class Stack<double> :public StackBase
{

    int arr[5];
public:
    Stack()
    {
        cout << "Stack generated for (Special for double)" << endl;
    }
    void Push(int val){ arr[++top] = val; }
    int Pop(){ return arr[top--]; }
    int Peek(){ return arr[top]; }

};
int main1()
{
    Stack<int> stk1;
    Stack<double> stk2;
    Stack<char*> stk3;
    Stack<char> stk4;
    
    return 0;
}

template<typename T1, typename T2>
class MyDictionary
{
protected:
    T1 key;
    T2 value;
public:
    void Iterate()
    {
        cout << "MyDictionary" << endl;
    }
};

template<typename T>
class Dictionary :public MyDictionary < int, T >
{

};

int main()
{
    MyDictionary<int, char*> dictionary1;
    dictionary1.Iterate();
    Dictionary<double> dictionary;
    Stack<char> stk4;
    
    return 0;
}
