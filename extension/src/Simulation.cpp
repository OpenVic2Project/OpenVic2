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

void OpenVic2::Date::incrementDate(){
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

Date OpenVic2::Date::getDate(){
	return this;
}

int OpenVic2::Simulation::getCurrentTime(){
	return this->current_time;
}

void OpenVic2::Simulation::setCurrentTime(std::chrono::time_point<std::chrono::high_resolution_clock> time){
	this->lastPolledTime = time;
}

void OpenVic2::Simulation::togglePauseState(){
	this->isPaused = !isPaused;
}

void OpenVic2::Simulation::getPauseState(){
	return this->isPaused;
}

void OpenVic2::Simulation::increaseSimulationSpeed(){
	switch (this->currentSpeed) {
	case(Speed::Speed1):
		this->currentSpeed = Speed::Speed2;
		break;
	case(Speed::Speed2):
		this->currentSpeed = Speed::Speed3;
		break;
	case(Speed::Speed3):
		this->currentSpeed = Speed::Speed4;
		break;
	case(Speed::Speed4):
		this->currentSpeed = Speed::Speed5;
		break;
	}
}

void OpenVic2::Simulation::decreaseSimulationSpeed(){
	switch (this->currentSpeed) {
	case(Speed::Speed2):
		this->currentSpeed = Speed::Speed1;
		break;
	case(Speed::Speed3):
		this->currentSpeed = Speed::Speed2;
		break;
	case(Speed::Speed4):
		this->currentSpeed = Speed::Speed3;
		break;
	case(Speed::Speed5):
		this->currentSpeed = Speed::Speed4;
		break;
	}
}

void OpenVic2::Simulation::setSimulationSpeed(int speed){
	switch(speed) {
	case(2):
		this->currentSpeed = Speed::Speed2;
		break;
	case(3):
		this->currentSpeed = Speed::Speed3;
		break;
	case(4):
		this->currentSpeed = Speed::Speed4;
		break;
	case(5):
		this->currentSpeed = Speed::Speed5;
		break;
	case(6):
		this->currentSpeed = Speed::Speed6;
		break;
	default:
		this->currentSpeed = Speed::Speed1;
		break;
	}
}

int OpenVic2::Simulation::getSimulationSpeed()
{
	return static_cast<int>(this->currentSpeed);
}

void OpenVic2::Simulation::conditionallyAdvanceSimulation() {
	if (!(this->isPaused)) {
		std::chrono::time_point<std::chrono::high_resolution_clock> previousTime = this->lastPolledTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count() >= this->getSimulationSpeed()) {
			this->lastPolledTime = currentTime;
			this->inGameDate.incrimentDate();
		}
	}

}
