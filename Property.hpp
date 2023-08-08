#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class SortCriteria
{
    MonthlyRent,
    Location,
    Size
};

class Property
{
public:
    Property *next;
    string ads_id;
    string prop_name;
    int completion_year;
    int monthly_rent;
    string location;
    string property_type;
    int rooms;
    int parking;
    int bathroom;
    int size;
    string furnished;
    vector<string> facilities;
    vector<string> additional_facilities;
    string region;

    Property(string ads_id, string prop_name, int completion_year, int monthly_rent,
             string location, string property_type, int rooms, int parking, int bathroom,
             int size, string furnished, vector<string> facilities,
             vector<string> additional_facilities, string region);

    void display() const;
};

class PropertyLinkedList
{
private:
    Property *head;
    Property *tail;

public:
    ~PropertyLinkedList();

    void insertAtEnd(Property *newProperty);
    void display(int numProperties) const;
    void sort_by_criterion(SortCriteria criterion);
};