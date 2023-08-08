#include "property.hpp"
#include <iostream>

Property::Property(string ads_id, string prop_name, int completion_year, int monthly_rent, string location,
                   string property_type, int rooms, int parking, int bathroom, int size, string furnished,
                   vector<string> facilities, vector<string> additional_facilities, string region)
    : ads_id(ads_id), prop_name(prop_name), completion_year(completion_year), monthly_rent(monthly_rent), location(location),
      property_type(property_type), rooms(rooms), parking(parking), bathroom(bathroom), size(size),
      furnished(furnished), facilities(facilities), additional_facilities(additional_facilities), region(region) {}

void Property::display() const
{
    cout << "Ads ID: " << ads_id
         << "\nProperty Name: " << prop_name
         << "\nCompletion Year: " << completion_year
         << "\nMonthly Rent (RM): " << monthly_rent
         << "\nLocation: " << location
         << "\nProperty Type: " << property_type
         << "\nRooms: " << rooms
         << "\nParking: " << parking
         << "\nBathroom: " << bathroom
         << "\nSize (sq. ft.): " << size
         << "\nFurnished: " << furnished
         << "\nFacilities: ";
    for (auto &facility : facilities)
    {
        cout << facility << ", ";
    }
    cout << "\nAdditional Facilities: ";
    for (auto &facility : additional_facilities)
    {
        cout << facility << ", ";
    }
    cout << "\nRegion: " << region;
    cout << "\n\n";
}

void PropertyLinkedList::insertAtEnd(Property *data)
{
    // The next property should be null, as this will be the last property in the list
    data->next = NULL;

    // If the list is empty, the head and tail should both be the new property
    if (head == NULL)
    {
        head = data;
        tail = data;
    }
    else
    {
        // Otherwise, add the new property to the end of the list and update the tail
        tail->next = data;
        tail = data;
    }
}

void PropertyLinkedList::display(int numRows) const
{
    Property *current = head;
    int count = 0;
    while (current != nullptr && count < numRows)
    {
        current->display();
        current = current->next;
        count++;
    }
}

PropertyLinkedList::~PropertyLinkedList()
{
    // Implement the destructor to free the memory used by the linked list nodes
    Property *current = head;
    while (current != nullptr)
    {
        Property *next = current->next;
        delete current;
        current = next;
    }
}

Property* PropertyLinkedList::getMiddle(Property *head)
{
    if (!head)
    {
        return head;
    }

    Property *slow = head;
    Property *fast = head->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

Property* PropertyLinkedList::merge(Property *a, Property *b)
{
    Property *result = nullptr;

    if (!a)
    {
        return b;
    }
    if (!b)
    {
        return a;
    }

    if (a->monthly_rent > b->monthly_rent ||
        (a->monthly_rent == b->monthly_rent && a->location > b->location) ||
        (a->monthly_rent == b->monthly_rent && a->location == b->location && a->size > b->size))
    {
        result = a;
        result->next = merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = merge(a, b->next);
    }

    return result;
}

Property* PropertyLinkedList::mergeSort(Property *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    Property *middle = getMiddle(head);
    Property *nextOfMiddle = middle->next;

    middle->next = nullptr;

    Property *left = mergeSort(head);
    Property *right = mergeSort(nextOfMiddle);

    Property *sortedList = merge(left, right);
    return sortedList;
}

void PropertyLinkedList::sortList() {
    head = mergeSort(head);
}

