#include <iostream>
#include "WaitingQueue.h"
#include "Bank.h"
using namespace std;
int main() {
    Bank b1;
    Customer c1 = Customer("Ali", 35, 62);
    Customer c2 = Customer("Mohamed",39, 57);
    Customer c3 = Customer("Ahmed", 78, 124);
    Customer c4 = Customer("Omar", 79, 32);
    Customer c5 = Customer("Adam", 80, 15);
    Customer c6 = Customer("Mostafa", 90, 10);
    Customer c7 = Customer("Gena", 95, 20);
    Customer c8 = Customer("Hanaa", 107, 20);

    b1.addCustomerToPriorityQueue(c1);
    b1.addCustomerToPriorityQueue(c2);
    b1.addCustomerToPriorityQueue(c3);
    b1.addCustomerToPriorityQueue(c4);
    b1.addCustomerToPriorityQueue(c5);
    b1.addCustomerToPriorityQueue(c6);
    b1.addCustomerToPriorityQueue(c7);
    b1.addCustomerToPriorityQueue(c8);

    cout << "Bank Simulation \n";
    cout << "===================\n";
    b1.run2();

    return 0;

}
