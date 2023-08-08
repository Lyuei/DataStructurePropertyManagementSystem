#pragma once

#include <string>
#include <iostream>
#include <vector>
using namespace std;

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

    Property(string ads_id, string prop_name, int completion_year, int monthly_rent, string location, string property_type, int rooms, int parking, int bathroom, int size, string furnished, vector<string> facilities, vector<string> additional_facilities, string region);

    void display() const;
};

class PropertyLinkedList
{
public:
    PropertyLinkedList() : head(nullptr), tail(nullptr) {}
    ~PropertyLinkedList();
    void insertAtEnd(Property *data);
    void display(int numRows) const;
    Property *mergeSort(Property *head);
    void sortList();

private:
    Property *head;
    Property *tail;
    Property *getMiddle(Property *head);
    Property *merge(Property *a, Property *b);
};