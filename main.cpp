#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void sort_trip(list<Goat>& trip);
void find_goat(list<Goat>& trip);
void average_age(list<Goat>& trip);
void reverse_trip(list<Goat>& trip);
void increment_age_trip (list<Goat>& trip);
void remove_duplicate_names(list<Goat>& trip);
void remove_oldest_goats(list<Goat>& trip);


int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }

    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }


    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t"
             << "[" << i++ << "] "
             << gt.get_name()
             << " (" << gt.get_age()
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void sort_trip(list<Goat>& trip)
{
    trip.sort([](Goat &a , Goat &b) {
        return (a.get_name()) > (b.get_name());
    });
    cout << "Shuffled trip: " << endl;
    display_trip(trip);
}

void find_goat(list<Goat>& trip)
{
    string name;
    cout << "Name of goat you would like to find: ";
    cin >> name;

    auto it = find_if(trip.begin(), trip.end(), [name](const Goat& v){ return v.get_name() == name; });
    if (it != trip.end()) {
        cout << name << " was found." << endl;
    }
    else
        cout << endl << name << " not found." << endl;
}

void average_age(list<Goat>& trip)
{
     int totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& v){ return sum + v.get_age(); });
     int totalAmount = trip.size();

     cout << "The average age of the goats in the trip are: " << totalAge / totalAmount << endl;
}

void clear_length(list<Goat>& trip)
{
    cout << "Clearing trip ... " << endl;
    trip.clear();
    cout << "Size now: " << trip.size();
}

void reverse_trip(list<Goat>& trip)
{
    reverse(trip.begin(), trip.end());
    cout << "Reversed trip: " << endl;
    display_trip(trip);
}

void increment_age_trip (list<Goat>& trip)
{
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat& v) {
              int i = v.get_age() + 1;
              v.set_age(i);
              return v; });
    cout << "New trip: " << endl;
    display_trip(trip);
}

void remove_duplicate_names(list<Goat>& trip)
{
    trip.erase(unique(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return (a.get_name()).compare(b.get_name()); }), trip.end());

}

void remove_oldest_goats(list<Goat>& trip)
{
    trip.erase(remove_if(trip.begin(), trip.end(), [](const Goat& v){ return v.get_age() == 20; }), trip.end());
}
