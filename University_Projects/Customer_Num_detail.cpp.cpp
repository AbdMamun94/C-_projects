#include<iostream>

using namespace std;

class Male;

enum Memory
{
    phone,
    simcard,
    sdcard
};

class CardFull: public exception{};

class Date
{
private:
    unsigned int day, month, year;
public:
    Date(unsigned int day=15, unsigned int month=3, unsigned int year=2013):day(day),month(month),year(year)
    {
        if(day>31||month>12||year<1900)
            throw "Wrong Date";
    }
    ~Date(){}
    friend ostream& operator<<(ostream&, Date&);
};

ostream& operator<<(ostream& out, Date& d)
{
    //return out<<d.year<<"-"<<(d.month<10?'0':'')<<d.month<<"-"<<(d.day<10?'0':'')<<d.day;
    return out<<d.year<<"-"<<d.month<<"-"<<d.day;
}

class Contact
{
private:
    int nr;
    string name;
    Memory storedIn;
public:
    Contact* next;
    Contact(int, string, Memory);
    void set_name(string);
    string get_name();
    void set_nr(int);
    int get_nr();
    void print_list();
    virtual void print()=0;
};

Contact::Contact(int nr, string name, Memory si=simcard):nr(nr),name(name),storedIn(si)
{
    next=NULL;
}

void Contact::set_name(string name)
{
    this->name=name;
}

string Contact::get_name()
{
    return name;
}

void Contact::set_nr(int nr)
{
    this->nr=nr;
}
int Contact::get_nr()
{
    return nr;
}

void Contact::print_list()
{
    Contact *p=this;
    while(p!=NULL)
    {
        p->print();
        p=p->next;
    }
}

class Friend:public Contact
{
private:
    Date birthday;
    bool remind;
public:
    Friend(int nr, string name, Date& birthday, bool remind=true):Contact(nr,name), birthday(birthday), remind(remind){}
    void change()
    {
        remind=(!remind);
    }
    void print()
    {
        //if(get_nr())
            cout<<get_nr()<<": "<<get_name()<<"\t"<<birthday;
        //else
            //cout<<get_nr()<<" not found";
    }
};

class Female: public Friend
{
public:
    Female(int nr, string name, Date& birthday):Friend(nr, name, birthday){}
    void print()
    {
        Friend::print();
        cout<<"(female)"<<endl;
    }
};

class Phone
{
public:
    Contact *contacts;
    Phone()
    {
        contacts=NULL;
    }
    void add(Contact *c)
    {
        c->next=contacts;
        contacts=c;
    }
    Contact *search(int nr)
    {
        Contact *temp;
        temp=contacts;
        while(temp!=NULL)
        {
            if(temp->get_nr()==nr)
                return temp;
            else
                temp=temp->next;

        }
        return NULL;
        //cout<<temp->get_nr()<<" not found";
    }
};


int main()
{
    Phone p;
    try
    {
        Date d1(03,05,1989);
        Date *d2=new Date(13,11, 2001);
        Female *lara=new Female(555, "Lara",d1);
        lara->change();
        p.add(lara);
        p.add(new Female(888, "Pia", *d2));
    }
    catch(CardFull)
    {
        cout<<"card full";
    }
    catch(string t)
    {
        cerr<<t;
    }
    p.contacts->print_list();
    Contact *c=p.search(222);
    if(c!=NULL)
        c->print();
    return 0;
}
