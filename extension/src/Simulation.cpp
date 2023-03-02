#include "Simulation.hpp"


OpenVic2::Date::Date(){
	this->day = 1;
	this->month = 1;
	this->year = 1836;
}

OpenVic2::Date::~Date(){
}

OpenVic2::Date::Date(uint64_t day, uint64_t month, uint64_t year){
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
	this->year = year;
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

void OpenVic2::Date::setDate(uint64_t day, uint64_t month, uint64_t year)
{
	this->day = day;
	this->month = month;
	this->year = year;
	
}

Date OpenVic2::Date::getDate()
{
	return Date();
}

int OpenVic2::Simulation::getCurrentTime(){
	return this->current_time;
}

void OpenVic2::Simulation::setCurrentTime(int time){
	this->currentTime = time;
}

void OpenVic2::Simulation::pauseGame(){
	this->isPaused = !isPaused;
}

void OpenVic2::Simulation::checkRealTime() {
	if (!(this->isPaused)) {
		std::chrono::time_point<std::chrono::high_resolution_clock> previousTime = this->currentTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();
		if ((currentTime - previousTime).count() >= 4) {
			this->currentTime = currentTime;
			this->inGameDate.incrimentDate();
		}
	}

}
