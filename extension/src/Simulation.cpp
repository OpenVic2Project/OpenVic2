#include "Simulation.hpp"

OpenVic2::Date::Date()::day(1), month(1), year(1836) {}

OpenVic2::Date::~Date(){
}

OpenVic2::Date::Date(int day, int month, int year){
	if (day <= 30){
		this->day = day;
	}
	else {
		this->day = 1;
	}
	if (month <= 12) {
		this->month = month;
	}
	else {
		this->month = 1;
	}
	if (year >= 1836 && year <= 1936) {
		this->year = year;
	}
	else {
		this->year = 1836;
	}
}

void OpenVic2::Date::incrimentDate(){
	if (this->day >= 30) {
		this->day = 1;
		this->month++;
		if (this->month > 12) {
			this->year++;
			this->month = 1;
		}
	}
	else {
		this->day++;
	}
}

void OpenVic2::Date::setDate(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
	
}

Date OpenVic2::Date::getDate()
{
	return Date();
}
