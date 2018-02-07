#include <iostream>
using namespace std;
class MyArray
{
    int arr[5];// {1, 2, 3, 4, 5};
    int length;
public:
    MyArray()
    {
        length = 5;
        arr[0] = 1;
        arr[1] = 2;
        arr[2] = 3;
        arr[3] = 4;
        arr[4] = 5;
    }
    
    class Helper
    {
        MyArray *ptr;
        int index;
    public:
        Helper(MyArray *ptr, int index) :ptr(ptr), index(index)
        {
        }
        Helper & operator=(int val)
        {
            cout << "Writing" << endl;
            this->ptr->arr[index] = val;
            return *this;
        }
        operator int()
        {
            cout << "Reading" << endl;
            return this->ptr->arr[index];
        }
        Helper & operator=(Helper hlp)
        {
            cout << "Reading/Writing" << endl;
            this->ptr->arr[index] = hlp.ptr->arr[hlp.index];
            return *this;
        }
    };
    
    Helper operator[](int index)
    {
        return Helper(this, index);
    }
    
    MyArray & Begin()
    {
        return *this;
    }
    class Iterator{
        int *arr;
        int length;
        int index = 0;
    public:
        Iterator(MyArray & obj) :arr(obj.arr), length(obj.length)
        {
        }
        void Reset()
        {
            this->index = 0;
        }
        int Next()
        {
            return arr[index++];
        }
        bool HasNext()
        {
            return this->index <= length;
        }
        int First()
        {
            this->Reset();
            return this->Next();
        }
        void ForEach(void(*FPTR)(int))
        {
            for (int it = this->First(); this->HasNext(); it = this->Next())
            {
                FPTR(it);
            }
        }
    };
    
};

void GetElement(int val)
{
    cout << val * 10 << endl;
}
int main()
{
    MyArray obj;
    obj[3] = 999;//writing
    int k = obj[2];//reading
    obj[1] = obj[0];//read/write
    cout << "k=" << k << endl;
    
    MyArray::Iterator itr = obj.Begin();
    itr.ForEach(GetElement);
    for (int it = itr.First(); itr.HasNext(); it = itr.Next())
    {
        cout << it << endl;
    }
    
    return 0;
}