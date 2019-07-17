#pragma once
#include <iostream>
#include <vector>
using namespace std;


//list of all existing airports
vector<Airport*> airport_manifest;
//list of all existing airlines
vector<Airline*> airline_manifest;

//days of the week
enum Day {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

//time and day
struct Date{
  Day day;
  int time;
  string printDate(){
    string date;
    switch(day){
      case Sunday: date = "Sunday";
      case Monday: date ="Monday";
      case Tuesday: date = "Tuesday";
      case Wednesday: date = "Wednesday";
      case Thursday: date = "Thursday";
      case Friday: date = "Friday";
      case Saturday: date = "Saturday";
    }
    date += " @ ";
    int m = time%100, h = (time/100)%12;
    date += h + ':' + m;
    if(time >= 1200) date += " p.m.";
    else date += " a.m.";
    return date;
  }
};

//location coordinates
struct Coordinates{
  float x, y;
  Coordinates(float lat, float long){
    x = long;
    y = lat;
  }
};

//flight (flight)
struct Flight{
  string airline;
  float time;
  Date date;
  float basePrice;
  Airport* connect;
  string printTime(){
    float frac, whole; frac = modf(time, &whole);
    int minutes, hours = whole;
    minutes = frac * 60;
    return "Hours: " + hours + " Minutes: " + minutes;
  }
};

//airport (vertex)
struct Airport{
  vector<Flight> flights;
  string name;
  int size;
  Coordinates location;
  float Distance(Flight);
  void setTime(Flight&);
  void setPrice(Flight&);
  bool setInfo();
  void addFlight(Airport*, Date, string);
};

//network of airports
struct Airline{
  string name;
  float rating;
  vector<Airport*> connections;
  string printRating();
  void addFlight();
  void editFlight(string);
  bool setInfo();
  float getPrice(Flight);
};

ostream& operator<<(ostream& out, Date& obj){return out << obj.printDate();}
ostream& operator<<(ostream& out, Flight& obj){return out << obj.printTime();}
ostream& operator<<(ostream& out, Airport& obj){return "(" + x + "," + y + ")";}
ostream& operator<<(ostream& out, Airline& obj){return out << obj.printRating();}
void printAllAirports();
void printAllAirlines();
void addAirport();
void addAirline();
void removeAirport(string);
void removeAirline(string);
void editAirport(string);
void editAirline(string);
Airport* find(string, vector<Airport*>);
Airline* find(string, vector<Airline*>);
bool exists(string, vector<Airport*>);
bool exists(string, vector<Airline*>);
