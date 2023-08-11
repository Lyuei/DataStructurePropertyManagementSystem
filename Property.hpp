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
    ~PropertyLinkedList();

    void insertAtEnd(Property *newProperty);
    void display(int numProperties) const;
    void mergeSortByCriterion(SortCriteria criterion);
    void quickSortByCriterion(SortCriteria criterion);

    Property *linearSearch(const string &criterion);
    Property* binarySearch(const std::string& criterion);
    void sortProperties();

    // // Mark a property as a favorite based on its unique identifier (e.g., ads_id)
    // void markFavorite(const string &ads_id)
    // {
    //     Property *current = head;
    //     while (current != nullptr)
    //     {
    //         if (current->getAdsId() == ads_id)
    //         {
    //             current->toggleFavorite();
    //             cout << "Property marked as favorite.\n";
    //             return;
    //         }
    //         current = current->next;
    //     }
    //     cout << "Property not found.\n";
    // }

    // // Display favorite properties
    // void displayFavorites() const
    // {
    //     Property *current = head;
    //     bool foundFavorite = false;
    //     while (current != nullptr)
    //     {
    //         if (current->isFavorite)
    //         {
    //             current->display();
    //             foundFavorite = true;
    //         }
    //         current = current->next;
    //     }
    //     if (!foundFavorite)
    //     {
    //         cout << "No favorite properties.\n";
    //     }
    // }
};