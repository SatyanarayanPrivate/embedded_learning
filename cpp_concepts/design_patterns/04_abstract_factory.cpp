#include<iostream>
#include<map>
#include<string>
using namespace std;

class IVideo
{
public:
    virtual void CreateVideo() = 0;
    virtual void PlayVideo() = 0;
};
class IAudio
{
public:
    virtual void CreateAudio() = 0;
    virtual void PlayAudio() = 0;
};
class IMagnifier
{
public:
    virtual void CreateMagnifier() = 0;
    virtual void AttachMagnifier() = 0;
};
class IFactory
{
public:
    virtual IVideo* CreateVideo() = 0;
    virtual IAudio* CreateAudio() = 0;
    virtual IMagnifier* CreateMagnifier() = 0;
};
//-------------
class IEVideo :public IVideo
{
public:
    virtual void CreateVideo()
    {
        cout << "IE Video Created" << endl;
    }
    virtual void PlayVideo()
    {
        cout << "IE Video Playing" << endl;
    }
};
class IEAudio :public IAudio
{
public:
    virtual void CreateAudio()
    {
        cout << "IE Audio Created" << endl;
    }
    virtual void PlayAudio()
    {
        cout << "IE Audio Playing" << endl;
    }
};
class IEMagnifier :public IMagnifier
{
public:
    virtual void CreateMagnifier()
    {
        cout << "IE Magnifier Created" << endl;
    }
    virtual void AttachMagnifier()
    {
        cout << "IE Magnifier Attached" << endl;
    }
};

class IEFactory :public IFactory
{
public:
    virtual IVideo* CreateVideo()
    {
        return new IEVideo();
    }
    virtual IAudio* CreateAudio(){
        return new IEAudio();
    }
    virtual IMagnifier* CreateMagnifier(){
        return new IEMagnifier();
    }
};

class ChromeVideo :public IVideo
{
public:
    virtual void CreateVideo()
    {
        cout << "Chrome Video Created" << endl;
    }
    virtual void PlayVideo()
    {
        cout << "Chrome Video Playing" << endl;
    }
};
class ChromeAudio :public IAudio
{
public:
    virtual void CreateAudio()
    {
        cout << "Chrome Audio Created" << endl;
    }
    virtual void PlayAudio()
    {
        cout << "Chrome Audio Playing" << endl;
    }
};
class ChromeMagnifier :public IMagnifier
{
public:
    virtual void CreateMagnifier()
    {
        cout << "Chrome Magnifier Created" << endl;
    }
    virtual void AttachMagnifier()
    {
        cout << "Chrome Magnifier Attached" << endl;
    }
};

class ChromeFactory :public IFactory
{
public:
    virtual IVideo* CreateVideo()
    {
        return new ChromeVideo();
    }
    virtual IAudio* CreateAudio(){
        return new ChromeAudio();
    }
    virtual IMagnifier* CreateMagnifier(){
        return new ChromeMagnifier();
    }
};

typedef IFactory* (*FPTR)();
IFactory * ReturnIE()
{
    return new IEFactory();
}
IFactory * ReturnChrome()
{
    return new ChromeFactory();
}
class Dummy
{
    static map<string, FPTR> MyMap;
public:
    Dummy();

    /*void Register(string key, FPTR fp)
     *	{
     *	MyMap[key] = fp;
}*/
    FPTR GetFromRegister(string key)
    {
        return MyMap[key];
    }
};
map<string, FPTR> Dummy::MyMap;
Dummy::Dummy()
{
    MyMap["Ie"] = ReturnIE;
    MyMap["Chrome"] = ReturnChrome;
}
Dummy dummy;
int main()
{
    //	Dummy dummy;
    cout << "Make a Choice Ie or Chrome " << endl;
    string key;
    cin >> key;
    IFactory *fact = dummy.GetFromRegister(key)(); //new IEFactory();

    IVideo *vid = fact->CreateVideo(); //new IEVideo();
    vid->CreateVideo();
    vid->PlayVideo();

    IMagnifier *mag = fact->CreateMagnifier(); //new IEMagnifier();
    mag->CreateMagnifier();
    mag->AttachMagnifier();

    IAudio *aud = fact->CreateAudio(); //new IEAudio();
    aud->CreateAudio();
    aud->PlayAudio();
    return 0;
}
