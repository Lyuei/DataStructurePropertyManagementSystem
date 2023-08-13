#pragma once

#include <string>
#include <iostream>
#include "CSVReader.hpp"
#include "PaymentManager.hpp"


using namespace std;

// Enumeration to represent the status of a rent request
enum class RentRequestStatus
{
    PENDING,
    APPROVED,
    DECLINED,
    PAID
};

class RentRequest
{
public:
    string userId;
    string adsId;
    RentRequestStatus status;
    PaymentManager paymentManager;

    // Constructors
    RentRequest() : status(RentRequestStatus::PENDING) {}
    RentRequest(const string &userId, const string &adsId)
        : userId(userId), adsId(adsId), status(RentRequestStatus::PENDING) {}
};

class RentRequestLinkedList
{
public:
    struct Node
    {
        RentRequest data;
        Node *next;

        Node(const RentRequest &request) : data(request), next(nullptr) {}
    };

    Node *head;

    RentRequestLinkedList() : head(nullptr) {}

    void insert(const RentRequest &request)
    {
        Node *newNode = new Node(request);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void displayUserRentHistory(const string &userId) const
    {
        Node *temp = head;
        bool found = false; // Flag to check if any rent request is found for the given user

        while (temp)
        {
            if (temp->data.userId == userId)
            {
                found = true;
                cout << "Ads ID: " << temp->data.adsId << ", Status: ";
                switch (temp->data.status)
                {
                case RentRequestStatus::PENDING:
                    cout << "Pending";
                    break;
                case RentRequestStatus::APPROVED:
                    cout << "Approved";
                    break;
                case RentRequestStatus::DECLINED:
                    cout << "Declined";
                    break;
                }
                cout << endl;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "No renting history found for the given user." << endl;
        }
    }

    void managePendingRentRequests(PropertyLinkedList &propertyList)
    {
        Node *temp = head;
        int count = 0;

        // List all pending requests
        cout << "Pending Rent Requests:\n";
        while (temp)
        {
            if (temp->data.status == RentRequestStatus::PENDING)
            {
                count++;
                string input = temp->data.adsId;
                propertyList.updateVectorFromList();
                propertyList.findPropertyByCriteria(SearchCriteria::ADS_ID, input, 0);
                cout << count << ". User ID: " << temp->data.userId << '\n';
            }
            temp = temp->next;
        }

        if (count == 0)
        {
            cout << "No pending rent requests at this time.\n";
            return;
        }

        // Ask the manager to choose a request to review
        int choice;
        cout << "Enter the number of the request to review, or 0 to exit: ";
        cin >> choice;

        if (choice <= 0 || choice > count)
        {
            cout << "Invalid choice. Exiting.\n";
            return;
        }

        // Find the selected request
        temp = head;
        int current = 0;
        while (temp)
        {
            if (temp->data.status == RentRequestStatus::PENDING)
            {
                current++;
                if (current == choice)
                    break;
            }
            temp = temp->next;
        }

        // Ask the manager to approve or decline
        char decision;
        cout << "Approve or Decline (A/D): ";
        cin >> decision;

        if (decision == 'A' || decision == 'a')
        {
            temp->data.status = RentRequestStatus::APPROVED;
            cout << "Request approved.\n";
        }
        else if (decision == 'D' || decision == 'd')
        {
            temp->data.status = RentRequestStatus::DECLINED;
            cout << "Request declined.\n";
        }
        else
        {
            cout << "Invalid input. Exiting without changes.\n";
        }
    }

    bool manageTenancyPayment(const string &userId, const string &adsId)
    {
        // Find the corresponding rent request
        Node *temp = head;
        while (temp)
        {
            if (temp->data.userId == userId && temp->data.adsId == adsId && temp->data.status == RentRequestStatus::APPROVED)
            {
                int totalAmount = calculateTotalAmount(temp->data);
                if (!processPayment(totalAmount))
                {
                    std::cout << "Payment failed. Please try again.\n";
                    return false;
                }

                // Update the status to PAID
                temp->data.status = RentRequestStatus::PAID;

                // Additional steps
                recordPayment(temp->data);
                generateReceipt(temp->data);

                std::cout << "Payment successful. Thank you for your payment.\n";
                return true;
            }
            temp = temp->next;
        }

        // Rent request not found or not in an approved state
        return false;
    }
};
