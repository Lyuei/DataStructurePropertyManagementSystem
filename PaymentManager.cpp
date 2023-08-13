#include "PaymentManager.hpp"
#include <iostream>

bool PaymentManager::manageTenancyPayment(RentRequest &rentRequest) {
    // Check if the rent request is approved
    if (rentRequest.status != RentRequestStatus::APPROVED) {
        std::cout << "Rent request is not approved. Payment cannot be processed.\n";
        return false;
    }

    // Calculate the total amount (this might include rent, deposit, etc.)
    int monthlyRent;

    // Process the payment (this could involve integration with a payment gateway)
    if (!processPayment(monthlyRent)) {
        std::cout << "Payment failed. Please try again.\n";
        return false;
    }

    // Update the rent request status to paid
    rentRequest.status = RentRequestStatus::PAID;

    // Record the payment in the tenant's payment history
    recordPayment(rentRequest);

    // Generate and provide a receipt
    generateReceipt(rentRequest);

    std::cout << "Payment successful. Thank you for your payment.\n";
    return true;
}




bool PaymentManager::processPayment(double amount)
{
    // Implementation...
}

void PaymentManager::recordPayment(const RentRequest &rentRequest)
{
    // Implementation...
}

void PaymentManager::generateReceipt(const RentRequest &rentRequest)
{
    // Implementation...
}
