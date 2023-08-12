#pragma once

#include <string>
#include <iostream>

// Enumeration to represent the status of a rent request
enum class RentRequestStatus {
    PENDING,
    APPROVED,
    DECLINED
};

class RentRequest {
public:
    std::string userId;
    std::string adsId;
    RentRequestStatus status;

    // Constructors
    RentRequest() : status(RentRequestStatus::PENDING) {}
    RentRequest(const std::string& userId, const std::string& adsId)
        : userId(userId), adsId(adsId), status(RentRequestStatus::PENDING) {}
};

class RentRequestLinkedList {
public:
    struct Node {
        RentRequest data;
        Node* next;
        
        Node(const RentRequest& request) : data(request), next(nullptr) {}
    };

    Node* head;

    RentRequestLinkedList() : head(nullptr) {}

    ~RentRequestLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(const RentRequest& request) {
        Node* newNode = new Node(request);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() const {
        Node* temp = head;
        while (temp) {
            std::cout << "User ID: " << temp->data.userId 
                      << ", Ads ID: " << temp->data.adsId 
                      << ", Status: ";
            switch (temp->data.status) {
                case RentRequestStatus::PENDING: std::cout << "Pending"; break;
                case RentRequestStatus::APPROVED: std::cout << "Approved"; break;
                case RentRequestStatus::DECLINED: std::cout << "Declined"; break;
            }
            std::cout << std::endl;
            temp = temp->next;
        }
    }
};