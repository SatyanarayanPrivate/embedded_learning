#include<iostream>
#include<map>
#include<string>
#include <typeinfo>
using namespace std;

struct GameObject
{
    static map<string, void(*)()> myMap;
    virtual ~GameObject()
    {
    }
};
map<string, void(*)()> GameObject::myMap;



struct SpaceShip:GameObject
{
};
struct SpaceStation :GameObject
{
};
struct Asteroid :GameObject
{
};

void Ship2Ship()
{
    cout << "Ship collides with ship" << endl;
}
void Ship2Station()
{
    cout << "Ship collides with station" << endl;
}
void Ship2Asteroid()
{
    cout << "Ship collides with Asteroid" << endl;
}
void Station2Asteroid()
{
    cout << "station collides with Asteroid" << endl;
}
class Register
{
public:
    Register()
    {
        string sp = typeid(SpaceShip).name();
        string st = typeid(SpaceStation).name();
        string at = typeid(Asteroid).name();
        GameObject::myMap[sp + sp] = Ship2Ship;
        GameObject::myMap[sp + st] = Ship2Station;
        GameObject::myMap[sp + at] = Ship2Asteroid;
        GameObject::myMap[st + at] = Station2Asteroid;
        
    }
}reg;
void ProcessCollission(GameObject &obj1,GameObject & obj2)
{
    string s1 = typeid(obj1).name();
    string s2 = typeid(obj2).name();
    GameObject::myMap[s1 + s2]();
    cout << "___________________________" << endl;
}
int main()
{
    SpaceShip sp;
    SpaceStation st;
    Asteroid ast;
    ProcessCollission(sp, sp);
    ProcessCollission(sp, st);
    ProcessCollission(sp, ast);
    ProcessCollission(st, ast);
    
    return 0;
}