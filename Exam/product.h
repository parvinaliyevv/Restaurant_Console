#pragma once
#include <iostream>
#include "exceptions.h"

using namespace std;
using namespace exceptions;

namespace kitchen {
	class Product {
	public:
		Product(const string& nameP, const int& caloriesP, const int& priceP) throw(MyException);
		Product& operator=(const Product& other) = delete;

		void SetName(const string& nameP) throw(MyException);
		void SetCalories(const int& caloriesP) throw(MyException);
		void SetPrice(const int& priceP) throw(MyException);

		const string& GetName() const noexcept { return _name; }
		const uint16_t& GetCalories() const noexcept { return _calories; }
		const uint16_t& GetPrice() const noexcept { return _price; }

		friend class Stock;

	private:
		string _name;
		uint16_t _calories;
		uint16_t _price;

	};
}
