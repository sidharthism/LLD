/**
 * @file SmartOTT.cpp
 * @author Sidharth S
 * @version 0.1
 * @date 2022-07-28
 *
 *
As a smart OTT company, we want to offer customized OTT plans for our customers
so that the customers should be able to choose to build their plan by choosing different
streaming platforms and how many viewing hours they want for each of them.
We do support the following streaming services and below is their tariff plan.

Streaming Service | Price per unit    | Unit in hours
Netflix           | Rs. 10            | 10 hrs
Amazon Prime      |   Rs. 2           | 5 hrs
Hotstar           | Rs. 1             | 5 hrs

Viewing hours can be subscribed based on the multiples of the above mentioned units only.
Based on the user’s choice, the system should show the total amount which should be paid by
the customer.

Sample Input 1
Viewing hours for Netflix: 20
Viewing hours for Amazon Prime: 10
Viewing hours for Hotstar: 50
Sample Output
Total amount should be paid: Rs.34 (10 * 2 + 2 * 2 + 1 * 10)

Sample Input 2
Viewing hours for Netflix: 10
Viewing hours for Amazon Prime: 0
Viewing hours for Hotstar: 100
Sample Output
Total amount should be paid: Rs.30 (10 * 1 + 2 * 0 + 1 * 20)

Sample Input 3
Viewing hours for Netflix: 10
Viewing hours for Amazon Prime: 2
Sample Output
Amazon Prime allows viewing hours in multiples of 5 only[3] [4]
 *
 *
 */

#include <iostream>
#include <vector>

using namespace std;

typedef enum
{
    failed,
    success
} SubscriptionStatus;

class Subscription
{
private:
    SubscriptionStatus status;
    int amount;

public:
    SubscriptionStatus getStatus() const
    {
        return this->status;
    }
    int getAmount() const
    {
        return this->amount;
    }
    Subscription(SubscriptionStatus status = failed, int amount = 0)
    {
        this->status = status;
        this->amount = amount;
    }
};

class StreamingService
{
private:
    string name;
    int unitInHours;
    int pricePerUnit;
    int noOfUnits(int viewingHours) const
    {
        if (unitInHours != 0)
            return (int)viewingHours / unitInHours;
        return 0;
    }
    bool validate_viewing_hours(int viewingHours) const
    {
        if (unitInHours != 0)
            return viewingHours % unitInHours == 0;
        return false;
    }
    int calculate_amount(int viewingHours) const
    {
        return unitInHours * noOfUnits(viewingHours);
    }

public:
    string getName() const
    {
        return name;
    }
    int getUnitInHours() const
    {
        return unitInHours;
    }
    Subscription subscribe(int viewingHours)
    {
        int amount = 0;
        SubscriptionStatus status = failed;
        bool viewingHoursValid = validate_viewing_hours(viewingHours);
        if (viewingHoursValid)
        {
            amount = calculate_amount(viewingHours);
            status = success;
        }
        return Subscription(status, amount);
    }
    StreamingService(string name, int pricePerUnit, int unitInHours)
    {
        this->name = name;
        this->pricePerUnit = pricePerUnit;
        this->unitInHours = unitInHours;
    }
};

class SmartOtt
{
private:
    vector<StreamingService> streamingServices;

public:
    Subscription build_subscription()
    {
        int hours, totalAmount = 0;
        for (StreamingService service : streamingServices)
        {
            cout << "Viewing hours for " << service.getName() << " : ";
            cin >> hours;
            Subscription serviceSub = service.subscribe(hours);
            if (serviceSub.getStatus() == failed)
            {
                cout << service.getName() << " allows viewing hours in multiples of " << service.getUnitInHours() << " only!" << endl;
                return Subscription(failed, 0);
            }
            totalAmount += serviceSub.getAmount();
        }
        return Subscription(success, totalAmount);
    }
    SmartOtt(vector<StreamingService> streamingServices)
    {
        this->streamingServices = streamingServices;
    }
};

int main(int argc, char *argv[])
{
    StreamingService netflix = StreamingService("Netflix", 10, 10);
    StreamingService amazonPrime = StreamingService("Amazon Prime", 2, 5);
    StreamingService hotstar = StreamingService("Hotstar", 1, 5);

    vector<StreamingService> streamingServices = {netflix, amazonPrime, hotstar};

    SmartOtt smartOtt = SmartOtt(streamingServices);
    Subscription new_subscription = (Subscription)smartOtt.build_subscription();
    if (new_subscription.getStatus() == success)
        cout << "Rs." << new_subscription.getAmount();
    return 0;
}

// class SubscriptionWithSplitUp : public Subscription
// {
//     private:
//     string splitUp;
//     public:
//     SubscriptionWithSplitUp()
//     :Subscription()
//     {

//     }
// }