#pragma once

#include <string>

using namespace std;

struct Property {
    string ads_id;
    string prop_name;
    int completion_year;
    double monthly_rent;
    string location;
    string property_type;
    int rooms;
    int parking;
    int bathroom;
    double size;
    string furnished;
    string facilities;
    string additional_facilities;
    Property *next; // Pointer

    Property() : next(nullptr) {}
};

void insertAtBeginning(Property **head, const string& adsId, const string& propName, int compYear, double rent,
                       const string& loc, const string& propType, int rms, int park,
                       int bath, double sz, const string& furnish, const string& fac,
                       const string& addFac);
