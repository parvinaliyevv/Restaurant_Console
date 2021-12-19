#include "provision.h"

namespace kitchen {
	void Provision::SetQuantity(const int& quantityP) {
		if (quantityP < NULL || quantityP > USHRT_MAX) throw ArgumentException("The quantity of product cannot be negative or fantasy!");
		this->_quantity = quantityP;
	}

	void Provision::Increase(const int& quantityP) {
		if (quantityP < NULL || quantityP > SHRT_MAX) throw ArgumentException("The quantity of product cannot be negative or fantasy!");
		else if (_quantity + quantityP > USHRT_MAX) throw ArgumentException("Insufficient storage space in the stock!");

		this->_quantity += quantityP;
	}
	void Provision::Decrease(const int& quantityP) {
		if (quantityP < NULL || quantityP > SHRT_MAX) throw ArgumentException("The quantity of product cannot be negative or fantasy!");
		else if (quantityP > this->_quantity) throw ArgumentException("Not enough product in stock!");

		this->_quantity -= quantityP;
	}
}
