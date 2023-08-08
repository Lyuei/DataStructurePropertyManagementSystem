#include "LinkedList.hpp"
#include <algorithm>
#include <iostream>

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

void LinkedList::searchTenantByUserId(string userId) {
    Node* current = head;
    bool tenantFound = false;
    while (current != NULL) {
        Tenant* tenant = dynamic_cast<Tenant*>(current->data);
        if (tenant != NULL) {
            // Search the userId field for the searchCriterion
            if (tenant->userId == userId) {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound) {
        cout << "It appears we've stumbled into a tenant-less desert with your criteria. Time to broaden the horizons!\n";
    }
}

void LinkedList::searchTenantByName(const string& searchCriterion) {
    Node* current = head;
    bool tenantFound = false;

    // Convert the search criterion to lowercase
    string searchCriterionLower = searchCriterion;
    transform(searchCriterionLower.begin(), searchCriterionLower.end(), searchCriterionLower.begin(), ::tolower);

    while (current != NULL) {
        Tenant* tenant = dynamic_cast<Tenant*>(current->data);
        if (tenant != NULL) {
            // Convert the tenant's name to lowercase
            string tenantNameLower = tenant->name;
            transform(tenantNameLower.begin(), tenantNameLower.end(), tenantNameLower.begin(), ::tolower);

            // Search the name field for the searchCriterion
            if (tenantNameLower.find(searchCriterionLower) != std::string::npos) {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound) {
        cout << "It appears we've stumbled into a tenant-less desert with your criteria. Time to broaden the horizons!\n";
    }
}


void LinkedList::searchTenantByAge(int age) {
    Node* current = head;
    bool tenantFound = false;
    while (current != NULL) {
        Tenant* tenant = dynamic_cast<Tenant*>(current->data);
        if (tenant != NULL) {
            // Compare the age field to the search criterion
            if (tenant->age == age) {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound) {
        cout << "It appears we've stumbled into a tenant-less desert with your criteria. Time to broaden the horizons!\n";
    }
}

void LinkedList::searchTenantByLastLogin(tm lastLogin) {
    Node* current = head;
    bool tenantFound = false;
    while (current != NULL) {
        Tenant* tenant = dynamic_cast<Tenant*>(current->data);
        if (tenant != NULL) {
            // Compare the lastLogin field to the search criterion
            // Note: this is a simple equality check, you might want to implement a more complex comparison
            if (tenant->lastLogin.tm_year == lastLogin.tm_year && 
                tenant->lastLogin.tm_mon == lastLogin.tm_mon && 
                tenant->lastLogin.tm_mday == lastLogin.tm_mday) {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound) {
        cout << "It appears we've stumbled into a tenant-less desert with your criteria. Time to broaden the horizons!\n";
    }
}

