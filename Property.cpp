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
    data->next = nullptr;

    // If the list is empty, the head and tail should both be the new property
    if (head == nullptr)
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

Property* merge_sorted_lists_enum(Property* left, Property* right, SortCriteria criterion) {
    // Create a dummy node to hold the merged list
    Property dummy("", "", 0, 0, "", "", 0, 0, 0, 0, "", {}, {}, "");
    Property* current = &dummy;

    while (left && right) {
        switch (criterion) {
            case SortCriteria::MonthlyRent:
                if (left->monthly_rent >= right->monthly_rent) {
                    current->next = left;
                    left = left->next;
                } else {
                    current->next = right;
                    right = right->next;
                }
                break;

            case SortCriteria::Location:
                if (left->location >= right->location) {
                    current->next = left;
                    left = left->next;
                } else {
                    current->next = right;
                    right = right->next;
                }
                break;

            case SortCriteria::Size:
                if (left->size >= right->size) {
                    current->next = left;
                    left = left->next;
                } else {
                    current->next = right;
                    right = right->next;
                }
                break;
        }

        current = current->next;
    }

    // Attach remaining nodes, if any
    if (left) current->next = left;
    if (right) current->next = right;

    return dummy.next;
}

pair<Property*, Property*> split_linked_list(Property* head) {
    if (!head || !head->next) return {head, nullptr};

    Property *slow = head, *fast = head, *prev = nullptr;
    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (prev) prev->next = nullptr;

    return {head, slow};
}

Property* merge_sort_linked_list(Property* head, SortCriteria criterion) {
    if (!head || !head->next) return head;

    // Split the linked list into two halves
    auto [left, right] = split_linked_list(head);

    // Recursively sort the two halves
    left = merge_sort_linked_list(left, criterion);
    right = merge_sort_linked_list(right, criterion);

    // Merge the sorted halves
    return merge_sorted_lists_enum(left, right, criterion);
}

void PropertyLinkedList::mergeSortByCriterion(SortCriteria criterion) {
    head = merge_sort_linked_list(head, criterion);
}

// Helper function to get the tail (last node) of the linked list
Property* getTail(Property* curr) {
    while (curr != nullptr && curr->next != nullptr) {
        curr = curr->next;
    }
    return curr;
}

// Partition the list using the last node as the pivot
Property* partition(Property* head, Property* end, Property*& newHead, Property*& newEnd, SortCriteria criterion) {
    Property* pivot = end;
    Property* prev = nullptr, *cur = head;
    Property* tail = pivot;

    // Initialize newHead and newEnd to pivot
    newHead = newEnd = pivot;

    while (cur != pivot) {
        bool condition = false;
        
        // Determine the sort condition based on the criterion
        switch (criterion) {
            case SortCriteria::MonthlyRent:
                condition = (cur->monthly_rent <= pivot->monthly_rent);
                break;
            // case SortCriteria::SquareFeet: // Hypothetical criterion for demonstration
            //     condition = (cur->square_feet <= pivot->square_feet);
            //     break;
            // ... add other criteria as needed
        }
        
        if (condition) {
            // If the current node is smaller or equal to the pivot
            if (newHead == pivot) {
                newHead = cur;
            }
            prev = cur; 
            cur = cur->next;
        } else {
            // If the current node is larger than the pivot
            if (prev) {
                prev->next = cur->next;
            }
            Property* tmp = cur->next;
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
Property* quickSortRecur(Property* head, Property* end, SortCriteria criterion) {
    if (!head || head == end) {
        return head;
    }

    Property* newHead = nullptr;
    Property* newEnd = nullptr;

    Property* pivot = partition(head, end, newHead, newEnd, criterion);

    if (newHead != pivot) {
        Property* tmp = newHead;
        while (tmp->next != pivot) {
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
void PropertyLinkedList::quickSortByCriterion(SortCriteria criterion) {
    head = quickSortRecur(head, getTail(head), criterion);
}
