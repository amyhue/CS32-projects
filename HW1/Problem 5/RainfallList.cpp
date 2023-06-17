#include "RainfallList.h"
#include <iostream>


RainfallList::RainfallList() {

}


bool RainfallList::add(unsigned long rainfall) {
	if (0 <= rainfall && rainfall <= 400) {
		if (rainfall_list.insert(rainfall) != -1) {
			return true;
		}
		// if there's room, the insert function will already insert (and would not return -1)
	}

	return false;
}


bool RainfallList::remove(unsigned long rainfall) {
	// find an index with rainfall's value in rainfall_list
	int rainIndex = rainfall_list.find(rainfall);
	if (rainIndex != -1) {
		return rainfall_list.erase(rainIndex);
	}

	return false;
}


int RainfallList::size() const {
	return rainfall_list.size();
}


// based on my add(), the rainfall is probably listed in order already
// but I want minimum() to not be too reliant on how add() is implemented
unsigned long RainfallList::minimum() const {
	if (size() == 0)
		return NO_RAINFALLS;

	unsigned long minRain, tempMin;
	rainfall_list.get(0, minRain);
	for (int i = 0; i < size(); i++) {
		rainfall_list.get(i, tempMin);
		if (tempMin < minRain)
			minRain = tempMin;
	}
	return minRain;
}

// based on my add(), the rainfall is probably listed in order already
// but I want minimum() to not be too reliant on how add() is implemented
unsigned long RainfallList::maximum() const {
	if (size() == 0)
		return NO_RAINFALLS;

	unsigned long maxRain, tempMax;
	rainfall_list.get(0, maxRain);
	for (int i = 0; i < size(); i++) {
		rainfall_list.get(i, tempMax);
		if (tempMax > maxRain)
			maxRain = tempMax;
	}
	return maxRain;

}


// Debugging
//void RainfallList::dump() const {
//	std::cerr << "Rainfall list:";
//	rainfall_list.dump();
//	std::cerr << std::endl << std::endl;
//}
