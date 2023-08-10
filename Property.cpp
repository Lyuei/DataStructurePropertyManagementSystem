#include "property.hpp"
#include <iostream>
#include <chrono>
#include <algorithm>

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
    // If the list is empty, the head and tail should both be the new property
    if (head == nullptr)
    {
        data->next = nullptr; // Set next to null only when you're sure you want to change it
        head = data;
        tail = data;
    }
    else
    {
        // Otherwise, add the new property to the end of the list and update the tail
        data->next = nullptr;
        tail->next = data;
        tail = data;
    }
}

// void PropertyLinkedList::insert(Property *newProperty)
// {
//     if (!newProperty)
//         return; // Null check

//     if (head == nullptr)
//     {
//         // If the list is empty, simply set the head to the new property
//         head = newProperty;
//     }
//     else
//     {
//         // If the list is not empty, traverse to the end and add the new property
//         Property *current = head;
//         while (current->next != nullptr)
//         {
//             current = current->next;
//         }
//         current->next = newProperty;
//     }
// }

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

Property *merge_sorted_lists_enum(Property *left, Property *right, SortCriteria criterion)
{
    // Create a dummy node to hold the merged list
    Property dummy("", "", 0, 0, "", "", 0, 0, 0, 0, "", {}, {}, "");
    Property *current = &dummy;

    while (left && right)
    {
        switch (criterion)
        {
        case SortCriteria::MonthlyRent:
            if (left->monthly_rent >= right->monthly_rent)
            {
                current->next = left;
                left = left->next;
            }
            else
            {
                current->next = right;
                right = right->next;
            }
            break;

        case SortCriteria::Location:
            if (left->location >= right->location)
            {
                current->next = left;
                left = left->next;
            }
            else
            {
                current->next = right;
                right = right->next;
            }
            break;

        case SortCriteria::Size:
            if (left->size >= right->size)
            {
                current->next = left;
                left = left->next;
            }
            else
            {
                current->next = right;
                right = right->next;
            }
            break;
        }

        current = current->next;
    }

    // Attach remaining nodes, if any
    if (left)
        current->next = left;
    if (right)
        current->next = right;

    return dummy.next;
}

pair<Property *, Property *> split_linked_list(Property *head)
{
    if (!head || !head->next)
        return {head, nullptr};

    Property *slow = head, *fast = head, *prev = nullptr;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (prev)
        prev->next = nullptr;

    return {head, slow};
}

Property *merge_sort_linked_list(Property *head, SortCriteria criterion)
{
    if (!head || !head->next)
        return head;

    // Split the linked list into two halves
    auto [left, right] = split_linked_list(head);

    // Recursively sort the two halves
    left = merge_sort_linked_list(left, criterion);
    right = merge_sort_linked_list(right, criterion);

    // Merge the sorted halves
    return merge_sorted_lists_enum(left, right, criterion);
}

void PropertyLinkedList::mergeSortByCriterion(SortCriteria criterion)
{
    auto start = chrono::high_resolution_clock::now();
    head = merge_sort_linked_list(head, criterion);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by Merge Sort: " << duration.count() / 1000000.0 << " seconds" << endl;
}

// Helper function to get the tail (last node) of the linked list
Property *getTail(Property *curr)
{
    while (curr != nullptr && curr->next != nullptr)
    {
        curr = curr->next;
    }
    return curr;
}

// Partition the list using the last node as the pivot
Property *partition(Property *head, Property *end, Property *&newHead, Property *&newEnd, SortCriteria criterion)
{
    if (end == nullptr)
    {
        // Handle the case where the end pointer is null
        return nullptr;
    }

    Property *pivot = end;
    Property *prev = nullptr, *cur = head;
    Property *tail = pivot;

    // Initialize newHead and newEnd to pivot
    newHead = newEnd = pivot;

    while (cur != pivot)
    {
        bool condition = false;

        // Determine the sort condition based on the criterion
        switch (criterion)
        {
        case SortCriteria::MonthlyRent:
            condition = (cur->monthly_rent >= pivot->monthly_rent);
            break;
        case SortCriteria::Location:
            condition = (cur->location >= pivot->location); // Modified to compare location
            break;
        case SortCriteria::Size:
            condition = (cur->size >= pivot->size); // Modified to compare size
            break;
        default:
            // Handle unexpected criterion value
            return nullptr;
        }

        if (condition)
        {
            // If the current node is smaller or equal to the pivot
            if (newHead == pivot)
            {
                newHead = cur;
            }
            prev = cur;
            cur = cur->next;
        }
        else
        {
            // If the current node is larger than the pivot
            if (prev)
            {
                prev->next = cur->next;
            }
            Property *tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur; // Update the tail
            cur = tmp;
        }
    }

    // Update the newEnd to the current tail after partitioning
    newEnd = tail;

    return pivot;
}

// Recursive quick sort function
Property *quickSortRecur(Property *head, Property *end, SortCriteria criterion)
{
    if (!head || head == end)
    {
        return head;
    }

    Property *newHead = nullptr;
    Property *newEnd = nullptr;

    Property *pivot = partition(head, end, newHead, newEnd, criterion);

    if (newHead != pivot)
    {
        Property *tmp = newHead;
        while (tmp->next != pivot)
        {
            tmp = tmp->next;
        }
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp, criterion);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd, criterion);

    return newHead;
}

// Main quick sort function

void PropertyLinkedList::quickSortByCriterion(SortCriteria criterion)
{
    auto start = chrono::high_resolution_clock::now();

    head = quickSortRecur(head, getTail(head), criterion);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by Quick Sort: " << duration.count() / 1000000.0 << " seconds" << endl;
}

// filterProperties function
PropertyLinkedList PropertyLinkedList::filter(const FilterCriteria &criteria) const
{
    PropertyLinkedList filteredList;
    Property *current = head;

    while (current != nullptr)
    {
        bool match = true;

        // Numeric filters
        match &= current->monthly_rent >= criteria.min_monthly_rent && current->monthly_rent <= criteria.max_monthly_rent;
        match &= current->completion_year >= criteria.min_completion_year && current->completion_year <= criteria.max_completion_year;
        match &= current->rooms >= criteria.min_rooms && current->rooms <= criteria.max_rooms;
        match &= current->parking >= criteria.min_parking && current->parking <= criteria.max_parking;
        match &= current->bathroom >= criteria.min_bathroom && current->bathroom <= criteria.max_bathroom;
        match &= current->size >= criteria.min_size && current->size <= criteria.max_size;

        // String filters
        if (!criteria.location.empty())
            match &= current->location == criteria.location;
        if (!criteria.property_type.empty())
            match &= current->property_type == criteria.property_type;
        if (!criteria.furnished.empty())
            match &= current->furnished == criteria.furnished;
        if (!criteria.region.empty())
            match &= current->region == criteria.region;

        // Vector filters
        for (const auto &facility : criteria.required_facilities)
        {
            if (find(current->facilities.begin(), current->facilities.end(), facility) == current->facilities.end())
            {
                match = false;
                break;
            }
        }

        for (const auto &additional_facility : criteria.required_additional_facilities)
        {
            if (find(current->additional_facilities.begin(), current->additional_facilities.end(), additional_facility) == current->additional_facilities.end())
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            // Deep copy the current Property node
            Property *newProperty = new Property(
                current->ads_id, current->prop_name, current->completion_year, current->monthly_rent,
                current->location, current->property_type, current->rooms, current->parking,
                current->bathroom, current->size, current->furnished, current->facilities,
                current->additional_facilities, current->region);

            filteredList.insertAtEnd(newProperty);
        }
        current = current->next;
    }

    return filteredList;
}
