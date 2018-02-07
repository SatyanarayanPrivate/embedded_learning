#include<iostream>
using namespace std;

// Decorator pattern:: dynamic extention of behavior
class ITunnel
{
public:
    virtual void TunnelMessage(char *msg) = 0;
};
//NULL object Pattern
class NullTunnel :public ITunnel
{
public:
    NullTunnel()
    {
    }
    void TunnelMessage(char *msg)
    {
    }
};
class TunnelHelper :public ITunnel
{
    ITunnel *tunnel;
protected:
    TunnelHelper(ITunnel *tunnel) :tunnel(tunnel)
    {
    }
public:
    void TunnelMessage(char *msg)
    {
        tunnel->TunnelMessage(msg);
    }
};
class LogTunnel :public TunnelHelper
{
public:
    LogTunnel(ITunnel *tnr) :TunnelHelper(tnr)
    {
    }
    void TunnelMessage(char *msg)
    {
        cout << "Logging msg (" << msg << ")" << endl;
        TunnelHelper::TunnelMessage(msg);
    }
};
class EncryptTunnel :public TunnelHelper
{
public:
    EncryptTunnel(ITunnel *tnr) :TunnelHelper(tnr)
    {
    }
    void TunnelMessage(char *msg)
    {
        cout << "Encrypting msg (" << msg << ")" << endl;
        TunnelHelper::TunnelMessage(msg);
    }
};
class EncodeTunnel :public TunnelHelper
{
public:
    EncodeTunnel(ITunnel *tnr) :TunnelHelper(tnr)
    {
    }
    void TunnelMessage(char *msg)
    {
        cout << "Encoding msg (" << msg << ")" << endl;
        TunnelHelper::TunnelMessage(msg);
    }
};
class TunnelFactory
{
    TunnelFactory()
    {
    }
    ~TunnelFactory()
    {
    }
public:
    static ITunnel * CreateTunnels()
    {
        //return new NullTunnel(); // always return null object instead of simple NULL.
        return new EncodeTunnel(new EncryptTunnel(new LogTunnel(new NullTunnel())));
    }
};
//-----------------------------------------
int main()
{
    cout << "Business Started ..." << endl;
    ITunnel *tunl = TunnelFactory::CreateTunnels();
    //if (tunl!=NULL)
    tunl->TunnelMessage("India is great");
    //Log
    cout << "Business Completed..." << endl;

    return 0;
}
