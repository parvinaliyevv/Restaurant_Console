#include "product.h"

namespace kitchen {
	Product::Product(const string& nameP, const int& caloriesP, const int& priceP) {
		SetName(nameP);
		SetCalories(caloriesP);
		SetPrice(priceP);
	}

	void Product::SetName(const string& nameP) {
		if (nameP.size() < 3) throw ArgumentException("Product name cannot be shorter than 3 characters!");
		this->_name = nameP;
	}
	void Product::SetCalories(const int& caloriesP) {
		if (caloriesP <= NULL || caloriesP > USHRT_MAX) throw ArgumentException("The number of calories cannot be negative, equal to null or fantasy!");
		this->_calories = caloriesP;
	}
	void Product::SetPrice(const int& priceP) {
		if (priceP <= NULL || priceP > USHRT_MAX) throw ArgumentException("The price of a product cannot be negative or equal to null or fantasy!");
		this->_price = priceP;
	}
}
