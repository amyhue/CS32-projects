//#include <iostream>
//#include <string>
//using namespace std;


//!***
// Make sure to delete all test about this line and after "Your declarations and implementations would go here."
class Event {
public:
    Event(string eventName);
    virtual ~Event();
    string name() const;
    virtual bool isSport() const;
    virtual string need() const = 0;

private:
    string m_name;
};

class BasketballGame : public Event{
public:
    BasketballGame(string basketballName);
    ~BasketballGame();
    virtual string need() const;
};

class Concert : public Event{
public:
    Concert(string concertName, string genre);
    ~Concert();
    virtual bool isSport() const;
    virtual string need() const;
private:
    string m_genre;
};

class HockeyGame : public Event{
public:
    HockeyGame(string hockeyName);
    ~HockeyGame();
    virtual string need() const;
};


//////////////
// Implementation
//////////////

// Event

Event::Event(string eventName)
: m_name(eventName){}

Event::~Event(){}

string Event::name() const {
    return m_name;
}

bool Event::isSport() const {
    return true;
}

// BasketballGame
BasketballGame::BasketballGame(string basketballName) 
: Event(basketballName){}

BasketballGame::~BasketballGame() {
    cout << "Destroying the " << name() << " basketball game" <<endl;
}

string BasketballGame::need() const {
    return "hoops";
}


// Concert
Concert::Concert(string concertName, string genre) 
: Event(concertName), m_genre(genre){}

Concert::~Concert() {
    cout << "Destroying the " << name() << " " << m_genre << " concert" << endl;
}

bool Concert::isSport() const{ 
    return false;
}

string Concert::need() const {
    return "a stage";
}

// HockeyGame
HockeyGame::HockeyGame(string hockeyName) 
: Event(hockeyName){}

HockeyGame::~HockeyGame() {
    cout << "Destroying the " << name() << " hockey game" << endl;
}

string HockeyGame::need() const {
    return "ice";
}



// !*** delete everything below
//Your declarations and implementations would go here

//void display(const Event* e)
//{
//    cout << e->name() << ": ";
//    if (e->isSport())
//        cout << "(sport) ";
//    cout << "needs " << e->need() << endl;
//}

//int main()
//{
//    Event* events[4];
//    events[0] = new BasketballGame("Lakers vs. Warriors");
//    // Concerts have a name and a genre.
//    events[1] = new Concert("Ricardo Arjona", "Latin pop");
//    events[2] = new Concert("Erykah Badu", "neo soul");
//    events[3] = new HockeyGame("Kings vs. Oilers");
//
//    cout << "Here are the events." << endl;
//    for (int k = 0; k < 4; k++)
//        display(events[k]);
//
//    // Clean up the events before exiting
//    cout << "Cleaning up." << endl;
//    for (int k = 0; k < 4; k++)
//        delete events[k];
//}
