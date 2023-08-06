#pragma once

#include "User.hpp"

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
    void insert(User *user);
    User *search(string userId);
    void deleteNode(string userId);
    User *login(string username, string password);
    void display() const; 
    void remove(string userId);
};