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

struct FilterCriteria
{
    // Numeric attributes with min and max values
    int min_monthly_rent = 0;
    int max_monthly_rent = INT_MAX;
    int min_completion_year = INT_MIN;
    int max_completion_year = INT_MAX;
    int min_rooms = 0;
    int max_rooms = INT_MAX;
    int min_parking = 0;
    int max_parking = INT_MAX;
    int min_bathroom = 0;
    int max_bathroom = INT_MAX;
    int min_size = 0;
    int max_size = INT_MAX;

    // String attributes for direct match (empty means no filter)
    string location = "";
    string property_type = "";
    string furnished = ""; // Assuming possible values might be "Yes", "No", etc.
    string region = "";

    // Vector attributes for contains filter
    vector<string> required_facilities;            // Properties should have all of these
    vector<string> required_additional_facilities; // Properties should have all of these
};

class Property
{
// private:
//     bool isFavorite;

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

    // bool isFavorite;

    std::vector<Property*> properties; // Declare the properties vector

public:
    PropertyLinkedList() : head(nullptr), tail(nullptr){};
    ~PropertyLinkedList();

    void insertAtEnd(Property *newProperty);
    // void insert(Property *newProperty);
    void display(int numProperties) const;
    void mergeSortByCriterion(SortCriteria criterion);
    void quickSortByCriterion(SortCriteria criterion);
    PropertyLinkedList filter(const FilterCriteria &criteria) const;
    bool adsIdExists(const std::string &ads_id) const;
    Property* linearSearch(const string &criterion);
};
