#ifndef BANK_H
#define BANK_H
#pragma once
#include <string>
#include "Customer.h"
#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

struct compareEventTime
{
    bool operator()(const Customer& cust1, Customer& cust2) const
    {
        return cust1.ArrivalTime > cust2.ArrivalTime;
    }
};
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
struct teller
{
    bool isAvailable;
    int tellerNumber;
    int numofserved;
    int availableTime;
    int totalTimeServed;
};

class Bank
{
private:
    priority_queue<Customer, vector<Customer>, compareEventTime> customerPriorityQueue;
    int teller_num = 3;


    queue<Customer> bankQueue;
    int currentTime = 0;
    teller* tellers;
    int totalWaitingTime = 0;
    int totalServiceTime = 0;
public:
    Bank()
    {
        tellers = new teller[teller_num];
        for (int i = 0; i < teller_num; ++i)
        {
            tellers[i].isAvailable = true;
            tellers[i].tellerNumber = i + 1;
            tellers[i].numofserved = 0;
            tellers[i].availableTime = 0;
            tellers[i].totalTimeServed = 0;

        }
    }

    ~Bank()
    {
        delete[] tellers;
    }

    void addCustomerToPriorityQueue(Customer c)
    {
        customerPriorityQueue.push(c);
    }

    void addCustomerToBankQueue(Customer c2)
    {
        bankQueue.push(c2);
    }

    void run()
    {
        while (!customerPriorityQueue.empty())
        {
            Customer cuurentCustomer = customerPriorityQueue.top();
            currentTime = cuurentCustomer.EventTime;
            customerPriorityQueue.pop();

            if (cuurentCustomer.EventType == "Arrival")
            {
                bool served = false;

                for (int i = 0; i < teller_num; i++)
                {
                    if (tellers[i].isAvailable)
                    {

                        cuurentCustomer.WaitingTime = currentTime - cuurentCustomer.EventTime;
                        cuurentCustomer.EventTime = currentTime + cuurentCustomer.ServiceTime;
                        cuurentCustomer.EventType = "Leave";
                        cout << "customer name : " << cuurentCustomer.name << " Waiting Time : " << cuurentCustomer.WaitingTime << " Service Time : " << cuurentCustomer.ServiceTime << " Leave Time : " << cuurentCustomer.EventTime << " served with teller number : " << tellers[i].tellerNumber << endl;
                        tellers[i].isAvailable = false;


                        totalServiceTime += cuurentCustomer.ServiceTime;
                        totalWaitingTime += cuurentCustomer.WaitingTime;
                        addCustomerToPriorityQueue(cuurentCustomer);
                        served = true;
                        break;
                    }
                }

                if (!served)
                {
                    addCustomerToBankQueue(cuurentCustomer);
                }
            }
            else if (cuurentCustomer.EventType == "Leave")
            {

                if (!bankQueue.empty())
                {

                    Customer current = bankQueue.front();
                    current.WaitingTime = currentTime - current.EventTime;
                    current.EventTime = currentTime + current.ServiceTime;
                    current.EventType = "Leave";
                    cout << "customer name : " << current.name << " Waiting Time : " << current.WaitingTime << " Service Time : " << current.ServiceTime << " Leave Time : " << current.EventTime << endl;
                    totalServiceTime += current.ServiceTime;
                    totalWaitingTime += current.WaitingTime;
                    addCustomerToPriorityQueue(current);
                    bankQueue.pop();

                }
                else
                {
                    for (int i = 0; i < teller_num; i++)
                    {
                        if (!tellers[i].isAvailable)
                        {
                            tellers[i].isAvailable = true;
                            break;
                        }
                    }
                }
            }
        }

        cout << "Total Sevice Time is : " << totalServiceTime << " and Total Waiting Time is : " << totalWaitingTime << endl;
    }

    teller* findNearestAvailableTeller()
    {
        teller* nearestTeller = nullptr;
        int earliestAvailableTime = INT_MAX;

        for (int i = 0; i < teller_num; i++)
        {
            if (tellers[i].availableTime < earliestAvailableTime)
            {
                nearestTeller = &tellers[i];
                earliestAvailableTime = tellers[i].availableTime;
            }
        }

        return nearestTeller;
    }
   void displayCustomerDetails(Customer c, teller t)
{
    cout << "Customer Name: " << c.name << endl;
    cout << "Waiting Time: " << c.WaitingTime << endl;
    cout << "Service Time: " << c.ServiceTime << endl;
    cout << "Leave Time: " << c.LeaveTime << endl;
    cout << "Served by Teller Number: " << t.tellerNumber << endl;
    cout << "-------------------------------------\n" << endl;
}

   void displayTellerDetails()
{
    cout << "Tellers Details: " << endl;
    for (int i = 0; i < teller_num; i++)
    {
        cout << "Teller Number: " << tellers[i].tellerNumber << endl;
        cout << "Total Time Served: " << tellers[i].totalTimeServed << endl;
        cout << "Number of Customers Served: " << tellers[i].numofserved << endl;
        cout << "-------------------------------------\n" << endl;
    }
}

    void displayAVG()
{
    cout << "Service and Waiting Details: " << endl;
    cout << "Total Service Time: " << totalServiceTime << endl;
    cout << "Total Waiting Time: " << totalWaitingTime << endl;
}
    void run2()
    {

        cout << endl;
        SetColor(19);
        cout << "Customers Details : " << endl;
        SetColor(14);
        while (!customerPriorityQueue.empty())
        {
            Customer cuurentCustomer = customerPriorityQueue.top();

            bool served = false;
            for (int i = 0; i < teller_num; i++)
            {
                if (tellers[i].isAvailable)
                {

                    cuurentCustomer.WaitingTime = cuurentCustomer.ArrivalTime - cuurentCustomer.ArrivalTime;
                    cuurentCustomer.LeaveTime = cuurentCustomer.ArrivalTime + cuurentCustomer.ServiceTime;
                    displayCustomerDetails(cuurentCustomer, tellers[i]);
                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = cuurentCustomer.LeaveTime;
                    tellers[i].numofserved++;

                    tellers[i].totalTimeServed += cuurentCustomer.ServiceTime;
                    totalServiceTime += cuurentCustomer.ServiceTime;
                    totalWaitingTime += cuurentCustomer.WaitingTime;
                    customerPriorityQueue.pop();
                    served = true;
                    break;
                }

            }

            if (!served)
            {


                teller* nearestTeller = findNearestAvailableTeller();

                    nearestTeller->isAvailable = true;
                    nearestTeller->numofserved++;
                    cuurentCustomer.WaitingTime = nearestTeller->availableTime - cuurentCustomer.ArrivalTime;
                    cuurentCustomer.LeaveTime = cuurentCustomer.ArrivalTime + cuurentCustomer.WaitingTime + cuurentCustomer.ServiceTime;
                    displayCustomerDetails(cuurentCustomer, *nearestTeller);
                    totalServiceTime += cuurentCustomer.ServiceTime;
                    totalWaitingTime += cuurentCustomer.WaitingTime;
                    nearestTeller->totalTimeServed += cuurentCustomer.ServiceTime;

                    nearestTeller->availableTime = cuurentCustomer.LeaveTime;
                    nearestTeller->isAvailable = false;
                    customerPriorityQueue.pop();



            }

        }

        displayTellerDetails();
        displayAVG();
    }

    void run3()
    {

        cout << endl;
        SetColor(19);
        cout << "Customers Details : " << endl;
        SetColor(14);
        while (!customerPriorityQueue.empty())
        {
            Customer cuurentCustomer = customerPriorityQueue.top();
            bool served = false;
            for (int i = 0; i < teller_num; i++)
            {
                if (tellers[i].isAvailable)
                {

                    cuurentCustomer.WaitingTime = cuurentCustomer.ArrivalTime - cuurentCustomer.ArrivalTime;
                    cuurentCustomer.LeaveTime = cuurentCustomer.ArrivalTime + cuurentCustomer.ServiceTime;
                    displayCustomerDetails(cuurentCustomer, tellers[i]);
                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = cuurentCustomer.LeaveTime;
                    tellers[i].numofserved++;

                    tellers[i].totalTimeServed += cuurentCustomer.ServiceTime;
                    totalServiceTime += cuurentCustomer.ServiceTime;
                    totalWaitingTime += cuurentCustomer.WaitingTime;
                    customerPriorityQueue.pop();
                    served = true;
                    break;
                }

            }

            if (!served)
            {


                teller* nearestTeller = findNearestAvailableTeller();

                nearestTeller->isAvailable = true;
                nearestTeller->numofserved++;
                cuurentCustomer.WaitingTime = nearestTeller->availableTime - cuurentCustomer.ArrivalTime;
                cuurentCustomer.LeaveTime = cuurentCustomer.ArrivalTime + cuurentCustomer.WaitingTime + cuurentCustomer.ServiceTime;
                displayCustomerDetails(cuurentCustomer, *nearestTeller);
                totalServiceTime += cuurentCustomer.ServiceTime;
                totalWaitingTime += cuurentCustomer.WaitingTime;
                nearestTeller->totalTimeServed += cuurentCustomer.ServiceTime;

                nearestTeller->availableTime = cuurentCustomer.LeaveTime;
                nearestTeller->isAvailable = false;
                customerPriorityQueue.pop();



            }

        }

        displayTellerDetails();
        displayAVG();
    }

};


#endif // BANK_H
