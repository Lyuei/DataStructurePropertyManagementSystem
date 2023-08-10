#include "LinkedList.hpp"
#include <algorithm>
#include <iostream>

void LinkedList::insert(User *user)
{
    Node *newNode = new Node();
    newNode->data = user;
    newNode->next = nullptr;

    // If the linked list is empty, make the new node the head
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    // Traverse the linked list to find the last node
    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    // Insert the new node at the end
    current->next = newNode;
}

User *LinkedList::login(string username, string password)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data->username == username && current->data->password == password)
        {
            // If the user is a manager and their status is false, do not allow them to log in
            Manager *manager = dynamic_cast<Manager *>(current->data);
            if (manager != NULL && !manager->status)
            {
                return NULL;
            }
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

void LinkedList::display() const
{
    Node *current = head;
    while (current != nullptr)
    {
        current->data->display();
        current = current->next;
    }
}

void LinkedList::remove(string userId)
{
    Node *current = head;
    Node *previous = nullptr;

    while (current != nullptr)
    {
        if (current->data->userId == userId)
        {
            // Found the node to delete
            if (previous == nullptr)
            {
                // The node to delete is the head of the list
                head = current->next;
            }
            else
            {
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

void LinkedList::setManagerStatusByUserId(string userId)
{
    Node *current = head;

    while (current != nullptr)
    {
        Manager *manager = dynamic_cast<Manager *>(current->data);

        if (manager != NULL && manager->userId == userId)
        {
            cout << "Enter new status (1 for active, 0 for inactive): ";
            bool newStatus;
            cin >> newStatus;

            if (newStatus == 1 || newStatus == 0)
            {
                manager->setStatus(newStatus); // Assuming there's a 'setStatus' method
                cout << "Status updated successfully!";
            }
            else
            {
                cout << "Invalid status entered. Please enter 1 for active or 0 for inactive.";
            }
            return; // Exit the method once the manager is found and status is updated
        }

        current = current->next;
    }

    cout << "Manager with User ID " << userId << " not found.";
}

void LinkedList::searchManagerByUserId(string userId)
{
    Node *current = head;
    bool managerFound = false;
    while (current != nullptr)
    {
        Manager *manager = dynamic_cast<Manager *>(current->data);
        if (manager != NULL)
        {
            // Search the userId field for the searchCriterion
            if (manager->userId == userId)
            {
                manager->display();
                managerFound = true;
            }
        }
        current = current->next;
    }
    if (!managerFound)
    {
        cout << "It appears we've stumbled into a barren wasteland with your criteria. Time to broaden the horizons!\n";
    }
}

void LinkedList::searchTenantByUserId(string userId)
{
    Node *current = head;
    bool tenantFound = false;
    while (current != nullptr)
    {
        Tenant *tenant = dynamic_cast<Tenant *>(current->data);
        if (tenant != NULL)
        {
            // Search the userId field for the searchCriterion
            if (tenant->userId == userId)
            {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound)
    {
        cout << "It appears we've stumbled into a barren wasteland with your criteria. Time to broaden the horizons!\n";
    }
}

void LinkedList::searchTenantByName(const string &searchCriterion)
{
    Node *current = head;
    bool tenantFound = false;

    // Convert the search criterion to lowercase
    string searchCriterionLower = searchCriterion;
    transform(searchCriterionLower.begin(), searchCriterionLower.end(), searchCriterionLower.begin(), ::tolower);

    while (current != nullptr)
    {
        Tenant *tenant = dynamic_cast<Tenant *>(current->data);
        if (tenant != NULL)
        {
            // Convert the tenant's name to lowercase
            string tenantNameLower = tenant->name;
            transform(tenantNameLower.begin(), tenantNameLower.end(), tenantNameLower.begin(), ::tolower);

            // Search the name field for the searchCriterion
            if (tenantNameLower.find(searchCriterionLower) != std::string::npos)
            {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound)
    {
        cout << "It appears we've stumbled into a tenant-less desert with your criteria. Time to broaden the horizons!\n";
    }
}

void LinkedList::searchTenantByAge(int age)
{
    Node *current = head;
    bool tenantFound = false;
    while (current != nullptr)
    {
        Tenant *tenant = dynamic_cast<Tenant *>(current->data);
        if (tenant != NULL)
        {
            // Compare the age field to the search criterion
            if (tenant->age == age)
            {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound)
    {
        cout << "It appears we've stumbled into a tenant-less desert with your criteria. Time to broaden the horizons!\n";
    }
}

void LinkedList::searchTenantByLastLogin(tm lastLogin)
{
    Node *current = head;
    bool tenantFound = false;
    while (current != nullptr)
    {
        Tenant *tenant = dynamic_cast<Tenant *>(current->data);
        if (tenant != NULL)
        {
            // Compare the lastLogin field to the search criterion
            // Note: this is a simple equality check, you might want to implement a more complex comparison
            if (tenant->lastLogin.tm_year == lastLogin.tm_year &&
                tenant->lastLogin.tm_mon == lastLogin.tm_mon &&
                tenant->lastLogin.tm_mday == lastLogin.tm_mday)
            {
                tenant->display();
                tenantFound = true;
            }
        }
        current = current->next;
    }
    if (!tenantFound)
    {
        cout << "It appears we've stumbled into a tenant-less desert with your criteria. Time to broaden the horizons!\n";
    }
}

// Helper function to compare two tm structs
bool isGreaterOrEqual(const tm &time1, const tm &time2)
{
    // Convert tm to time_t
    time_t t1 = mktime(const_cast<tm *>(&time1));
    time_t t2 = mktime(const_cast<tm *>(&time2));
    return t1 >= t2;
}

LinkedList LinkedList::filter(const TenantFilterCriteria &criteria)
{
    LinkedList filteredList; // The new linked list that will store the filtered results
    Node *current = head;    // Start from the head of the linked list

    while (current)
    {
        // Safely cast the User* to Tenant* using dynamic_cast
        Tenant *tenant = dynamic_cast<Tenant *>(current->data);

        if (tenant)
        { // Check if the cast was successful
            bool match = true;

            if (!criteria.name.empty() && tenant->name != criteria.name)
            {
                match = false;
            }

            if (!(tenant->age >= criteria.min_age && tenant->age <= criteria.max_age))
            {
                match = false;
            }

            if (criteria.useDate)
            {
                // Use the helper function for tm comparison
                if (!(isGreaterOrEqual(tenant->lastLogin, criteria.startDate) && isGreaterOrEqual(criteria.endDate, tenant->lastLogin)))
                {
                    match = false;
                }
            }

            if (match)
            {
                filteredList.insert(tenant); // Insert the matched tenant into the new linked list
            }
        }

        current = current->next; // Move to the next node in the linked list
    }

    return filteredList;
}

bool LinkedList::searchByUsername(const string &username) const
{
    Node *current = head;
    while (current)
    {
        if (current->data->getUsername() == username)
        {
            return true; // Found a match
        }
        current = current->next;
    }
    return false; // No match found
}
