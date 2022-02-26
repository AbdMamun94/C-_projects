
#include<iostream>
#include <exception>
#include<string>

using namespace std;
//Task 1
enum Cargo{
        bag,
        skis,
        suitcase
    };

ostream &operator<<(ostream& out, Cargo& c)
{
    switch(c)
    {
        case 0: out<<"bag"; break;
        case 1: out<<"skis"; break;
        case 2: out<<"suitcase"; break;
        default: out<<"";
    }
    return out;
}
//Task 2
class Seat
{
private:
    int row;
    char seat;

public:
    Seat(int row=0, char seat='?'): row(row),seat(seat){}

    bool  operator==(const Seat& a)                              // public definition of an overloaded num comparison operator ==, two seat objects are same having same row and same seat in a row
    {
        return ((this->row==a.row)&&(this->seat==a.seat));
    }

    friend ostream& operator<<(ostream&, Seat);
};
 // ( 2.2 )
ostream& operator <<(ostream& out, Seat c)
{
    out<<c.row<<" "<<c.seat<<endl;      // which shall write the row , a blank and the seat in the row onto the output stream
    return out;
}
//Task 3
class Payload
{
private:
    Payload *next;
public:
    Payload();
    virtual ~Payload();
    void set_next(Payload* p);
    Payload *get_next();
    /*{
        return next;
    } */
    void printAll();

    virtual void print()=0;  // pure virtual function
};

// 3.2
Payload::Payload()
{
    next=NULL;    // pointer attribute shall be initialized by a null pointer.
}

// 3.3
Payload::~Payload(){
    /**delete Payload;**/
};

// 3.4
void Payload::set_next(Payload *p)
{
    //next=p;
}

 // 3.5
Payload *Payload::get_next()
{
    return next;
}

// 3.6
void Payload::printAll(){
    //print();
    Payload *temp = this;
    while(temp!=NULL)
    {
        temp->printAll();
        temp = temp->next;
    }

}
//Task 4
class Freight:public Payload
{
private:
    Cargo cargo;
    int id,weight;

public:
    Freight(Cargo cargo, int id, int weight):cargo(cargo),id(id),weight(weight){}

    virtual~Freight(){}

    int get_weight(){
        return weight;
    }

    virtual void print()            // Virtual member function
    {
        cout<<"cargo "<<cargo<<":id =" <<id<<", weight ="<<get_weight()<<"g"<<endl;  // (cargo or freight)
    }
};

//Task 5
class Passenger:public Payload
{
private:
    string name;
    Seat seat;
    bool veggie;

public:
    Passenger(string name, bool veggie): name(name),veggie(veggie){}

   virtual~Passenger(){}

    string get_name()
    {
        return name;
    }

   int get_weight()
   {
        int pWeight=7500;      // returning for all passangers 7500g
        return pWeight;

    }

    void set_seat(Seat Z){
        this->seat=Z;
    }

    bool invert()
    {                                    // without parameter of return value inverting the value of the boolean attribute
        if (veggie)
            return false;
        else
            return true;
    }

    void print()
    {
        cout<<"Economy Class Passenger: "<<endl;
        cout<<name<<","<<"seat:"<<seat<<endl;
        if(veggie)
            cout<<"(vegetarian) "<<endl;
    }
};

//Task 6
class Economy: public Passenger
{
public:
    Economy(string name, bool veggie=false)  // no veggitarian as a default perameter
    :Passenger(name,veggie){}

    virtual void print()
    {
        cout<<"Economy Class Passenger: ";
        Passenger::print();
    }
};

// Task 7
class Flight
{
private:
    string code;
    float weight;
    Payload *payload;

public:/*problem */         /* public definition of a simplest possible class with name In Complete data derived from the predefined standard class for exceptions */
    class IncompleteData
    {
        public:
            string name;
            IncompleteData(Passenger *p)
            {
                name = p->get_name();
            }
    };

    Flight (string code, float weight=0.0, Payload *payload=NULL)
    :code(code),weight(weight),payload(payload){}

    void load(Freight *fr){
            weight+=(weight+fr->get_weight())/1000;
            Payload *newfr = fr;
            newfr->set_next(payload);
            payload = newfr;
    }

    void board (Passenger *p, Seat s){
            if(p==NULL){
                throw IncompleteData(p);
                Seat(0,'?');
            }
            else{
                weight+=(weight + p->get_weight())/1000;
                p->set_seat(s);
                Payload *newfr = p;
                newfr->set_next(payload);
                payload = newfr;
            }

    }
    void print(){
        cout<<"Flight: "<<code<<" with total weight payload: "<<weight<<"kg"<<endl;
        payload ->print ();
    }
};

//Task 8
int main()
{
    Flight f1("LH 123");  // Define an object variable f of type Flight with code LH 128

    Flight f2("LH 123");

    Freight s(skis, 456, 6800); // Define an object variable s of type Freight for skis with ID 456 and weight 6800g

    f1.load(&s);    // load the skis S onto Flight f.

    try{
        Freight *b=new Freight(bag, 789, 1800); //

        f2.load(b);    // Load the bag b onto Flight f

        Passenger *p1=new Passenger("Wally", true);   // Board a new passanger Wally on the heap with vegetarian meals onto Seat s.
        f1.board(p1,Seat(23,'A'));                     // Define an object variable s of type Seat initialize with seat 23A.

        Passenger *p2=new Passenger("Dilbert", false);    // Board a new passanger Dilbert on the heap onto seat 27D.
        f2.board(p2, Seat(27, 'D'));
    }
    catch (Flight::IncompleteData i){
        cout<<i.name<<"***incompleteData***"<<endl;
    }
    f1.print();
    f2.print();
    return 0;

    /*
    Flight f("LH 128");
    Freight s(skis, 456, 6800);
    f.load(&s);
    try
    {
    Freight*b = new Freight(bag,789,1800);
    f.load(b);
    f.doard(Seat s(23 'A'));
    passanger *p= new passanger ("wally" , vagie=true);
    f.board(p,s);
    f.board(p.seat(23,'A' ));
    Passenger *p1=new Passenger("Dilbert", vagie=false);
        f.board(p1, Seat(27, 'D'));
    }

    catch (Flight::IncompleteData i){
        cout<<i.name<<"***incompleteData***"<<endl;
    }
    f.print();
    f->print();
    return 0;  */
}

