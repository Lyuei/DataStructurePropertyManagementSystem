#pragma once

#include <iostream>
#include <string>

struct FavouriteProperty {
    std::string ads_id;
    std::string userId;
};

class FavouritePropertyLinkedList {
private:
    struct Node {
        FavouriteProperty data;
        Node* next;
        
        Node(const FavouriteProperty& prop) : data(prop), next(nullptr) {}
    };

    Node* head;

public:
    FavouritePropertyLinkedList() : head(nullptr) {}

    void insert(const FavouriteProperty& prop) {
        Node* newNode = new Node(prop);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() const {
        Node* temp = head;
        while (temp) {
            std::cout << "Ads ID: " << temp->data.ads_id 
                      << ", User ID: " << temp->data.userId << std::endl;
            temp = temp->next;
        }
    }

    // Function to display favorite properties for a specific user
    void displayForUser(const std::string& userId) const {
        Node* temp = head;
        int index = 1;
        while (temp) {
            if (temp->data.userId == userId) {
                std::cout << "Index: " << index
                          << ", Ads ID: " << temp->data.ads_id << std::endl;
            }
            temp = temp->next;
            index++;
        }
    }

    // Function to retrieve adsId by index (for user selection)
    std::string getAdsIdAtIndex(int index) const {
        Node* temp = head;
        int currentIndex = 1;
        while (temp) {
            if (currentIndex == index) {
                return temp->data.ads_id;
            }
            temp = temp->next;
            currentIndex++;
        }
        return "";  // Return empty string if index not found
    }

    // Function to check if a property exists at a given index
    bool propertyAtIndexExists(int index) const {
        Node* temp = head;
        int currentIndex = 1;
        while (temp) {
            if (currentIndex == index) {
                return true;
            }
            temp = temp->next;
            currentIndex++;
        }
        return false;
    }
};
