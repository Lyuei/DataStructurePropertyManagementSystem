#include "LinkedList.hpp"

void LinkedList::insert(User *user)
{
    Node *newNode = new Node();
    newNode->data = user;
    newNode->next = head;
    head = newNode;
}

User* LinkedList::login(string username, string password) {
    Node* current = head;
    while (current != NULL) {
        if (current->data->username == username && current->data->password == password) {
            // If the user is a manager and their status is false, do not allow them to log in
            Manager* manager = dynamic_cast<Manager*>(current->data);
            if (manager != NULL && !manager->status) {
                return NULL;
            }
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}


void LinkedList::display() const {
    Node* current = head;
    while (current != NULL) {
        current->data->display();
        current = current->next;
    }
}

void LinkedList::remove(string userId) {
    Node* current = head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->data->userId == userId) {
            // Found the node to delete
            if (previous == NULL) {
                // The node to delete is the head of the list
                head = current->next;
            } else {
                // The node to delete is in the middle or end of the list
                previous->next = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}
