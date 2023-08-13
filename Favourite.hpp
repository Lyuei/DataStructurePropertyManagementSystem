#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "Property.hpp"
#include "CSVReader.hpp"

using namespace std;

struct FavouriteProperty
{
    string ads_id;
    string userId;
};

class FavouritePropertyLinkedList
{
private:
    struct Node
    {
        FavouriteProperty data;
        Node *next;

        Node(const FavouriteProperty &prop) : data(prop), next(nullptr) {}
    };

    Node *head;

public:
    FavouritePropertyLinkedList() : head(nullptr) {}

    void insert(const FavouriteProperty &prop)
    {
        Node *newNode = new Node(prop);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() const
    {
        Node *temp = head;
        while (temp)
        {
            cout << "Ads ID: " << temp->data.ads_id
                 << ", User ID: " << temp->data.userId << endl;
            temp = temp->next;
        }
    }

    // Function to display favorite properties for a specific user
    void displayForUser(const string &userId) const
    {
        Node *temp = head;
        int index = 1;
        while (temp)
        {
            if (temp->data.userId == userId)
            {
                cout << "Index: " << index
                     << ", Ads ID: " << temp->data.ads_id << endl;
            }
            temp = temp->next;
            index++;
        }
    }

    // Function to retrieve adsId by index (for user selection)
    string getAdsIdAtIndex(int index) const
    {
        Node *temp = head;
        int currentIndex = 1;
        while (temp)
        {
            if (currentIndex == index)
            {
                return temp->data.ads_id;
            }
            temp = temp->next;
            currentIndex++;
        }
        return ""; // Return empty string if index not found
    }

    // Function to check if a property exists at a given index
    bool propertyAtIndexExists(int index) const
    {
        Node *temp = head;
        int currentIndex = 1;
        while (temp)
        {
            if (currentIndex == index)
            {
                return true;
            }
            temp = temp->next;
            currentIndex++;
        }
        return false;
    }

    void summarizeTop10Properties(PropertyLinkedList &propertyList) const
    {
        // Use a map to store the count of each ads_id
        map<string, int> propertyCount;

        // Traverse the linked list and count favorite properties
        Node *temp = head;
        while (temp)
        {
            propertyCount[temp->data.ads_id]++;
            temp = temp->next;
        }

        // Create a vector of pairs (ads_id, count) for sorting
        vector<pair<string, int>> propertyVector(propertyCount.begin(), propertyCount.end());

        // Sort the vector based on the count in descending order
        sort(propertyVector.begin(), propertyVector.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });

        // Display the top 10 favorite properties
        int count = 0;
        for (const auto &pair : propertyVector)
        {
            if (count >= 10)
            {
                break; // Display only the top 10 properties
            }
            string input = pair.first;
            propertyList.updateVectorFromList();
            propertyList.findPropertyByCriteria(SearchCriteria::ADS_ID, input, 0);
            cout << "Ads ID: " << pair.first << ", Favorite Count: " << pair.second << endl;
            count++;
        }
    }
};
