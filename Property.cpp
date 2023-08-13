#include "property.hpp"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <functional>

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
        return pair<Property *, Property *>{head, nullptr};

    Property *slow = head, *fast = head, *prev = nullptr;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (prev)
        prev->next = nullptr;

    return pair<Property *, Property *>{head, slow};
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

Property *PropertyLinkedList::linearSearch(const SearchCriteria &criteria, const string &str_value, int int_value)
{
    Property *current = head;
    while (current != nullptr)
    {
        bool match = false;
        switch (criteria)
        {
        case SearchCriteria::ADS_ID:
            match = current->ads_id == str_value;
            break;
        case SearchCriteria::PROP_NAME:
            match = current->prop_name == str_value;
            break;
        case SearchCriteria::LOCATION:
            match = current->location == str_value;
            break;
        case SearchCriteria::PROPERTY_TYPE:
            match = current->property_type == str_value;
            break;
        case SearchCriteria::FURNISHED:
            match = current->furnished == str_value;
            break;
        case SearchCriteria::REGION:
            match = current->region == str_value;
            break;
        case SearchCriteria::COMPLETION_YEAR:
            match = current->completion_year == int_value;
            break;
        case SearchCriteria::MONTHLY_RENT:
            match = current->monthly_rent == int_value;
            break;
        case SearchCriteria::ROOMS:
            match = current->rooms == int_value;
            break;
        case SearchCriteria::PARKING:
            match = current->parking == int_value;
            break;
        case SearchCriteria::BATHROOM:
            match = current->bathroom == int_value;
            break;
        case SearchCriteria::SIZE:
            match = current->size == int_value;
            break;
        }

        if (match)
        {
            current->display();
            return current;
        }

        current = current->next;
    }

    return nullptr; // Property not found
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

// Function to check if a given ads_id is present in the linked list
bool PropertyLinkedList::adsIdExists(const std::string &ads_id) const
{
    Property *current = head;
    while (current)
    {
        if (current->ads_id == ads_id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool PropertyLinkedList::compareAdsId(Property *a, Property *b)
{
    return a->ads_id < b->ads_id;
}

Property *PropertyLinkedList::binarySearch(const SearchCriteria &criteria, const string &str_value, int int_value)
{
    // Define our comparison functions for string and integer
    function<bool(Property *, Property *)> comparator;
    // cout << str_value;
    // Set the appropriate comparison function based on the search criteria
    switch (criteria)
    {
    case SearchCriteria::ADS_ID:
        comparator = [](Property *a, Property *b)
        { return a->ads_id < b->ads_id; };
        break;
    case SearchCriteria::PROP_NAME:
        comparator = [](Property *a, Property *b)
        { return a->prop_name < b->prop_name; };
        break;
    case SearchCriteria::LOCATION:
        comparator = [](Property *a, Property *b)
        { return a->location < b->location; };
        break;
    case SearchCriteria::PROPERTY_TYPE:
        comparator = [](Property *a, Property *b)
        { return a->property_type < b->property_type; };
        break;
    case SearchCriteria::FURNISHED:
        comparator = [](Property *a, Property *b)
        { return a->furnished < b->furnished; };
        break;
    case SearchCriteria::REGION:
        comparator = [](Property *a, Property *b)
        { return a->region < b->region; };
        break;
    case SearchCriteria::COMPLETION_YEAR:
        comparator = [](Property *a, Property *b)
        { return a->completion_year < b->completion_year; };
        break;
    case SearchCriteria::MONTHLY_RENT:
        comparator = [](Property *a, Property *b)
        { return a->monthly_rent < b->monthly_rent; };
        break;
    case SearchCriteria::ROOMS:
        comparator = [](Property *a, Property *b)
        { return a->rooms < b->rooms; };
        break;
    case SearchCriteria::PARKING:
        comparator = [](Property *a, Property *b)
        { return a->parking < b->parking; };
        break;
    case SearchCriteria::BATHROOM:
        comparator = [](Property *a, Property *b)
        { return a->bathroom < b->bathroom; };
        break;
    case SearchCriteria::SIZE:
        comparator = [](Property *a, Property *b)
        { return a->size < b->size; };
        break;
    }

    // Sort the properties based on the comparator
    sort(properties.begin(), properties.end(), comparator);

    // Now, use the appropriate comparison function based on whether we're searching by string or integer
    switch (criteria)
    {
    // String-based search
    case SearchCriteria::ADS_ID:
    case SearchCriteria::PROP_NAME:
    case SearchCriteria::LOCATION:
    case SearchCriteria::PROPERTY_TYPE:
    case SearchCriteria::FURNISHED:
    case SearchCriteria::REGION:
    {
        auto it = lower_bound(properties.begin(), properties.end(), str_value,
                              [&criteria](Property *prop, const string &value)
                              {
                                  switch (criteria)
                                  {
                                  case SearchCriteria::ADS_ID:
                                      return prop->ads_id < value;
                                  case SearchCriteria::PROP_NAME:
                                      return prop->prop_name < value;
                                  case SearchCriteria::LOCATION:
                                      return prop->location < value;
                                  case SearchCriteria::PROPERTY_TYPE:
                                      return prop->property_type < value;
                                  case SearchCriteria::FURNISHED:
                                      return prop->furnished < value;
                                  case SearchCriteria::REGION:
                                      return prop->region < value;
                                  default:
                                      return false;
                                  }
                              });

        if (it != properties.end())
        {
            for (; it != properties.end(); ++it)
            {
                bool matched = false;
                switch (criteria)
                {
                case SearchCriteria::ADS_ID:
                    if ((*it)->ads_id == str_value)
                    {
                        matched = true;
                        (*it)->display();
                    }
                    break;
                case SearchCriteria::PROP_NAME:
                    if ((*it)->prop_name == str_value)
                    {
                        matched = true;
                        (*it)->display();
                    }
                    break;
                case SearchCriteria::LOCATION:
                    if ((*it)->location == str_value)
                    {
                        matched = true;
                        (*it)->display();
                    }
                    break;
                case SearchCriteria::PROPERTY_TYPE:
                    if ((*it)->property_type == str_value)
                    {
                        matched = true;
                        (*it)->display();
                    }
                    break;
                case SearchCriteria::FURNISHED:
                    if ((*it)->furnished == str_value)
                    {
                        matched = true;
                        (*it)->display();
                    }
                    break;
                case SearchCriteria::REGION:
                    if ((*it)->region == str_value)
                    {
                        matched = true;
                        (*it)->display();
                    }
                    break;
                }
                if (!matched)
                {
                    break; // If the property doesn't match the criteria, exit the loop
                }
            }
        }
        break;
    }

    // Integer-based search
    default:
    {
        auto it = lower_bound(properties.begin(), properties.end(), int_value,
                              [&criteria](Property *prop, int value)
                              {
                                  switch (criteria)
                                  {
                                  case SearchCriteria::COMPLETION_YEAR:
                                      return prop->completion_year < value;
                                  case SearchCriteria::MONTHLY_RENT:
                                      return prop->monthly_rent < value;
                                  case SearchCriteria::ROOMS:
                                      return prop->rooms < value;
                                  case SearchCriteria::PARKING:
                                      return prop->parking < value;
                                  case SearchCriteria::BATHROOM:
                                      return prop->bathroom < value;
                                  case SearchCriteria::SIZE:
                                      return prop->size < value;
                                  default:
                                      return false;
                                  }
                              });

        for (; it != properties.end(); ++it)
        {
            bool matched = false;
            switch (criteria)
            {
            case SearchCriteria::COMPLETION_YEAR:
                if ((*it)->completion_year == int_value)
                {
                    matched = true;
                    (*it)->display();
                }
                break;
            case SearchCriteria::MONTHLY_RENT:
                if ((*it)->monthly_rent == int_value)
                {
                    matched = true;
                    (*it)->display();
                }
                break;
            case SearchCriteria::ROOMS:
                if ((*it)->rooms == int_value)
                {
                    matched = true;
                    (*it)->display();
                }
                break;
            case SearchCriteria::PARKING:
                if ((*it)->parking == int_value)
                {
                    matched = true;
                    (*it)->display();
                }
                break;
            case SearchCriteria::BATHROOM:
                if ((*it)->bathroom == int_value)
                {
                    matched = true;
                    (*it)->display();
                }
                break;
            case SearchCriteria::SIZE:
                if ((*it)->size == int_value)
                {
                    matched = true;
                    (*it)->display();
                }
                break;
            }
            if (!matched)
            {
                break; // Exit the loop when the current property no longer matches
            }
        }
        break;
    }
        
    }return nullptr;
}

void PropertyLinkedList::updateVectorFromList()
{
    properties.clear();       // Clear the current vector
    Property *current = head; // Assuming 'head' is the start of your linked list
    while (current)
    {
        properties.push_back(current);
        current = current->next;
    }
}

int PropertyLinkedList::getMonthlyRentByAdsId(const string &adsId) const {
    Property *temp = head;

    // Traverse the linked list and search for the property with the given ads_id
    while (temp) {
        if (temp->ads_id == adsId) {
            return temp->monthly_rent; // Return the monthly rent if the property is found
        }
        temp = temp->next;
    }

    cout << "Property with ads_id " << adsId << " not found.\n";
    return -1; // Return a sentinel value to indicate that the property was not found
}
