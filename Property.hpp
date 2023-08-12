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
<<<<<<< HEAD

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
=======
    PropertyLinkedList filter(const FilterCriteria &criteria) const;
    bool adsIdExists(const std::string &ads_id) const;
};
>>>>>>> 1e6a91079e2a670eb0105ed5eb31fd324e1e0442
