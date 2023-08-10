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
    LinkedList() : head(nullptr) {}
    Node *begin() { return head; }
    const Node *begin() const { return head; }
    Node *end() { return nullptr; }
    void insert(User *user);
    // User *search(string userId);
    // void deleteNode(string userId);
    User *login(string username, string password);
    void display() const;
    void remove(string userId);
    void searchTenantByUserId(string userId);
    void searchManagerByUserId(string userId);
    void searchTenantByName(const string &searchCriterion);
    void searchTenantByAge(int age);
    void searchTenantByLastLogin(tm lastLogin);
    void setManagerStatusByUserId(string userId);
    LinkedList filter(const TenantFilterCriteria &criteria);
    bool searchByUsername(const string &username) const;

    vector<Tenant *> to_vector() const
    {
        vector<Tenant *> vec;
        Node *current = head;
        while (current != nullptr)
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
