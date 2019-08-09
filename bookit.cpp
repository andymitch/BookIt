#include "bookit.hpp"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
float Airline::Distance(Flight to){
  float x = (this->location.x - to.connect->location.x); if(x < 0) x *= (-1);
  float y = (this->location.y - to.connect->location.y); if(y < 0) y *= (-1);
  return (sqrt(pow(x,2) + pow(y,2)) * 69);
}
void Airline::setTime(Flight& to){
  to.time = Distance(to) / 500;
}
void Airline::setPrice(Flight& to){
  float rate = (this->size + to.connect->size)/2;
  to.basePrice = Distance(to) / (rate * 3);
}
bool Airport::setInfo(){
  cout << "Name: ";
  cin.ignore();
  getline(cin, name);
  cout << endl;
  int sz = 0;
  while(sz < 1 || sz > 4){
    cout << "Size (1-4): ";
    cin >> sz;
    cout << endl;
  }
  size = sz;
  if(exists(name, airport_manifest)) return false;
  else return true;
}
void Airline::addFlight(Airport* to, Date d, string a){
  Flight flight;
  flight.connect = to;
  this->setPrice(flight);
  this->setTime(flight);
  flight.date = d;
  flight.airline = a;
  this->flights.push_back(flight);
}

void addAirport(){
  Airport* airport = new Airport();
  if(!airport->setInfo()){
    cout << "Airport already exists." << endl;
    delete airport;
  }else ::airport_manifest.push_back(airport);
}
void removeAirport(string name){
  if(exists(name, airport_manifest)){
    for(auto airline : airline_manifest){
      if(exists(name, airline->connections)){
        //delete all flights TO airport
        //delete all flights FROM airport
        //delete airport pointer from all airlines
      }
    }
    //temp ptr to airport
    //delete airport pointer from manifest
    //delete airport
  }else cout << "Airport does not exist." << endl;
}
void editAirport(string name){
  int choice = 0;
  cout << "\t1. name\n\t2. size\n\t3. location\n";
  while(choice < 1 || choice > 3){
    cout << "What would you like to change? (1-3):";
    cin >> choice;
  }
  Airport* airport = find(name, airport_manifest);
  switch(choice){
    case 1:{string _name;
      cout << "What is the new name?: "; cin >> _name; cout << endl;
      cout << airport->name << " -> " << _name << endl;
      airport->name = _name;
      break;}
    case 2:{int _size = 0;
      cout << "What is the new size? (1-4): ";
      while(_size < 1 || _size > 4) cin >> _size;
      cout << airport->size << " -> " << _size << endl;
      airport->size = _size;
      break;}
    case 3:{cout << "What is the new location?\n";
      int lat = 100, lon = 200;
      while(abs(lat) > 90){cout << "Latitude: "; cin >> lat; cout << endl;}
      while(abs(lon) > 180){cout << "longitude: "; cin >> lon; cout << endl;}
      Coordinates _loc(lat,lon);
      cout << airport->location << " -> " << _loc << endl;
      airport->location = _loc;
      break;}
  }
}

Airport* find(string name, vector<Airport*> list){
  for(auto airport : list){
    if(airport->name == name) return airport;
  }
  return NULL;
}
bool exists(string name, vector<Airport*> list){
  Airport* airport = find(name, list);
  return airport != NULL;
}
void printAllAirports(){
  int count = 1;
  for(auto airport : airport_manifest){
    cout << count << "\t" << airport->name << endl;
    count++;
  }
}
///////////////////////////////////////////////////////////////////////////////
string Airline::printRating(){
  int starCount = 0;
  string stars, full = "\u2605", empty = "\u2606", half = "\u2BEA";
  float frac, _whole; frac = modf(rating, &_whole); int whole = _whole;
  for(int i = 0; i < whole; i++){
    stars += full;
    starCount++;
  }
  if(frac >= .3 && frac <= .7){
    stars += half;
    starCount++;
  }
  for(starCount; starCount < 5; starCount++) stars += empty;
  return stars;
}
void Airline::addFlight(){
  int from = 0, to = 0, time = 3000; string _day;
  printAllAirports();

  cout << "what airport would you like to add a connection FROM?: ";
  while(from < 1 || from > airport_manifest.size()) cin >> from;
  cout << "what airport would you like to add a connection TO?: ";
  while(to < 1 || to > airport_manifest.size() || to == from){
    cin >> to;
    if(to == from) cout << "Chose a different airport." << endl;
  }

  cout << "What day of the week? (eg. Wednesday): ";
  while(!(cin >> _day)){
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "\nEnter a valid day of the week: ";
  }
  Day day = getDay(_day);
  cout << "What time? (0000-2359): ";
  while(time < 0000 || time > 2359 || time%100 > 59) cin >> time;
  Date d(day, time);

  connections[from-1]->addFlight(connections[to-1], d, this->name);
}
void Airline::editFlightTime(string name){
  //editTime
  Flight* flight = getFlight(name);
  int t = -1;
  cout << "Current flight time: " << flight->date.time << endl;
  while(!isdigit(t) || t < 0000 || t > 2359){
    cout << "What is the new time?: (0000-2359)";
    cin >> t;
  }
  flight->date.time = t;
}
bool Airline::setInfo(){
  cout << "Name: "; cin >> name; cout << endl;
  float rt = 0;
  while(rt <= 0 || rt > 5){
    cout << "Rating (0-5): "; cin >> rt; cout << endl;
  }
  rating = rt;
  if(exists(name, airline_manifest)) return false;
  else return true;
}
float Airline::getPrice(Flight flight){
  return (rating * 10) + flight.basePrice;
}

void addAirline(){
  Airline* airline = new Airline;
  if(!airline->setInfo()){
    cout << "Airline already exists." << endl;
    delete airline;
  }else ::airline_manifest.push_back(airline);
}
void removeAirline(string name){

}
void editAirline(string name){
  int choice = 0;
  cout << "\t1. name\n\t2. rating\n";
  while(choice < 1 || choice > 2){
    cout << "What would you like to change? (1-2):";
    cin >> choice;
  }
  Airline* airline = find(name, airline_manifest);
  switch(choice){
    case 1:{string _name;
      cout << "What is the new name?: "; cin >> _name; cout << endl;
      cout << airline->name << " -> " << _name << endl;
      airline->name = _name;
      break;}
    case 2:{float _rating = 0;
      cout << "What is the new rating? (1.0-5.0): ";
      while(_rating < 1 || _rating > 5) cin >> _rating;
      cout << airline->rating << " -> " << _rating << endl;
      airline->rating = _rating;
      break;}
  }
}

Airline* find(string name, vector<Airline*> list){
  for(auto airline : list){
    if(airline->name == name) return airline;
  }
  return NULL;
}
bool exists(string name, vector<Airline*> list){
  Airline* airline = find(name, list);
  return airline != NULL;
}
void printAllAirlines(){
  for(auto airline : airline_manifest) cout << "\t" << airline->name << endl;
}
///////////////////////////////////////////////////////////////////////////////
