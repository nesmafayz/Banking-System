#ifndef CUSTOMER_H
#define CUSTOMER_H
#pragma once
#include <string>
using namespace std;
class Customer
{


public:
	string name;
	int EventTime;
	string EventType="Arrival";
	int WaitingTime;
	int ServiceTime;
	int age;
	int hasplat;
	int hasVIP;
	bool served=false;
	int LeaveTime;


	Customer(){}

	int ArrivalTime, LeavingTime;
	Customer(string name, int arrivalTime, int serviceTime)
	{
		this->name = name;
		this->ArrivalTime = arrivalTime;
		this->ServiceTime = serviceTime;

	}

	Customer(string name, int arrivalTime, int serviceTime , int vip)
	{
		this->name = name;
		this->ArrivalTime = arrivalTime;
		this->ServiceTime = serviceTime;
		this->hasVIP = vip;

	}

};


#endif // CUSTOMER_H
