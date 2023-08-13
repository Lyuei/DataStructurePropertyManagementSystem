#pragma once

#include "RentRequest.hpp"

class PaymentManager {
public:
    bool manageTenancyPayment(RentRequest &rentRequest);

private:
    double calculateTotalAmount(const RentRequest &rentRequest);
    bool processPayment(double amount);
    void recordPayment(const RentRequest &rentRequest);
    void generateReceipt(const RentRequest &rentRequest);
};
