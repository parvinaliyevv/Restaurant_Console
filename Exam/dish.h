#pragma once
#include <iostream>
#include <iomanip>

#include "interface.h"
#include "exceptions.h"

using namespace std;
using namespace exceptions;

namespace food {
	class Dish {
	public:
		Dish(Interface* dishP, const int& quantityP) throw(MyException) : dish(dishP) { SetAmount(quantityP); }
		Dish& operator=(const Dish& other) = delete;

		void SetAmount(const int& quantityP) throw(MyException);
		const int16_t& GetAmount() const noexcept { return _quantity; }

		void Increase(const int& quantityP) throw(MyException);
		void Decrease(const int& quantityP) throw(MyException);

		friend ostream& operator<<(std::ostream& out, const Dish& obj) {
			out << std::left;

			out << setw(30) << obj.dish->GetName() << SEPARATOR
				<< setw(10) << obj.dish->GetIngredientsCalories() << SEPARATOR
				<< setw(10) << obj.dish->GetPrice() << SEPARATOR
				<< setw(10) << obj._quantity << SEPARATOR << endl;

			return out;
		}

	public:
		shared_ptr<Interface> dish;

	private:
		int16_t _quantity;

	};
}
