#include "dish.h"

namespace food {
	void Dish::SetAmount(const int& amountP) {
		if (amountP <= NULL || amountP > SHRT_MAX) throw ArgumentException("The amount of the dish cannot be negative or fantastic!");
		this->_amount = amountP;
	}

	void Dish::Increase(const int& amountP) {
		if (amountP < NULL || amountP > SHRT_MAX) throw ArgumentException("The amount of the dish cannot be negative or fantastic!");
		else if (_amount + amountP > USHRT_MAX) throw ArgumentException("Insufficient storage space in the stock!");

		this->_amount += amountP;
	}
	void Dish::Decrease(const int& amountP) {
		if (amountP < NULL || amountP > SHRT_MAX) throw ArgumentException("The amount of the dish cannot be negative or fantastic!");
		else if (amountP > this->_amount) throw ArgumentException("Not enough dish in stock!");

		this->_amount -= amountP;
	}
}
