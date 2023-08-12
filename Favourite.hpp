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

    ~FavouritePropertyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

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
};