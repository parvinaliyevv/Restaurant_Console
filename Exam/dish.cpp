#include "dish.h"

namespace food {
	void Dish::SetAmount(const int& quantityP) {
		if (quantityP <= NULL || quantityP > SHRT_MAX) throw ArgumentException("The amount of the dish cannot be negative, equal to null or fantastic!");
		this->_quantity = quantityP;
	}

	void Dish::Increase(const int& quantityP) {
		if (quantityP < NULL) throw ArgumentException("The amount of the dish cannot be negative!");
		else if (_quantity + quantityP > SHRT_MAX) throw ArgumentException("Insufficient storage space in the stock!");

		this->_quantity += quantityP;
	}
	void Dish::Decrease(const int& quantityP) {
		if (quantityP < NULL || quantityP > SHRT_MAX) throw ArgumentException("The amount of the dish cannot be negative!");
		else if (quantityP > this->_quantity) throw ArgumentException("Not enough dish in stock!");

		this->_quantity -= quantityP;
	}
}
