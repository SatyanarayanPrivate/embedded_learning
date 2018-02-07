#include<iostream>
using namespace std;
class Bank
{
public:
    void DoJob()
    {
        cout << "Open Db" << endl;
        DoDelayedJob();
        cout << "Close db" << endl;
    }
protected:
    virtual void DoDelayedJob() = 0;
};

class SbAccount :public Bank
{
public:
protected:
    void DoDelayedJob()
    {
        cout << "perform Sb Acoount job" << endl;
    }
    
};

class CurrentAccount :public Bank
{
public:
protected:
    void DoDelayedJob()
    {
        cout << "perform Current Acoount job" << endl;
    }
};

int main()
{
    SbAccount obj;
    obj.DoJob();
    cout << "_______________________" << endl;
    CurrentAccount obj1;
    obj1.DoJob();
    cout << "_______________________" << endl;
    
    return 0;
}