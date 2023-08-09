#pragma once

#include "User.hpp"
#include <vector>

// Node to hold user data
struct Node
{
    User *data; // Store pointer to User object
    Node *next;
};

// Linked list class
class LinkedList
{
private:
    Node *head;

public:
    LinkedList() : head(NULL) {}
    Node *begin() { return head; }
    Node *end() { return nullptr; }
    void insert(User *user);
    // User *search(string userId);
    // void deleteNode(string userId);
    User *login(string username, string password);
    void display() const;
    void remove(string userId);
    void searchTenantByUserId(string userId);
    void searchManagerByUserId(string userId);
    void searchTenantByName(const string& searchCriterion);
    void searchTenantByAge(int age);
    void searchTenantByLastLogin(tm lastLogin);
    void setManagerStatusByUserId(string userId);
    void setStatus(bool newStatus);

    vector<Tenant *> to_vector() const
    {
        vector<Tenant *> vec;
        Node *current = head;
        while (current != NULL)
        {
            Tenant *tenant = dynamic_cast<Tenant *>(current->data);
            if (tenant != nullptr)
            {
                vec.push_back(tenant);
            }
            current = current->next;
        }
        return vec;
    }
};

