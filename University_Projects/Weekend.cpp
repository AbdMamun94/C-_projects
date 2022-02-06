#include<iostream>
#include<iomanip>
using namespace std;

enum Service
{
    daily,
    weekend,
    workdays
};

ostream& operator <<(ostream& out, Service & s)
{
    switch(s)
    {
        case 0: out<<"daily" ; break;
        case 1: out<<"weekend" ; break;
        case 2: out<<"workdays" ; break;
        default : out<<" ";
    }
    return out;
}

class Time
{
private:
    unsigned int min;
public:
    class TimeWrong:public exception{};
    Time()
    {
        min = 0;
    }
unsigned int get_min()
    {
        return min;
    }
Time(unsigned int min ,unsigned int hour)
    {
        min = hour*60 + min;
        if (min>hour*60 + min)
            throw TimeWrong();
    }

    friend ostream& operator <<(ostream& out, Time &t)
    {
        return out<<setw(2)<<setfill('0')<<(t.min/60)<<":"<<setw(2)<<setfill('0')<<t.min%60;
    }
};

class Trasport
{
private:
    string arr,dep;
    Time depT,arrT;
public:
    Trasport(string arr,string dep,Time depT,Time arrT);
    ~Trasport();
    unsigned int get_duration();
    virtual void print();
};

Trasport::Trasport(string arr,string dep,Time depT,Time arrT):dep(dep),arr(arr),depT(depT),arrT(arrT)
{

}
Trasport::~Trasport() {}
unsigned int Trasport::get_duration()
{
    return arrT.get_min()-depT.get_min();
}

void Trasport::print()
{
    cout<<depT<<": leave" <<dep<<endl;
    cout<<arrT<<": arrive" <<arr<<endl;
}
class Local:class Trasport
{
private:
    int no;
    bool delay;
    Service service;

public:
    Local(string dep, string arr, Time depT, Time arrT, int no,Service service,bool delay=false :Trasport(dep,arr,depT,arrT),no(no),delay(delay),service(service))
{
}

};

int main()
{

}
