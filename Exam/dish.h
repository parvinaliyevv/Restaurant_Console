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
		Dish(Interface* dishP, const int& amountP) throw(MyException) : dish(dishP) { SetAmount(amountP); }
		Dish& operator=(const Dish& other) = delete;

		void SetAmount(const int& amountP) throw(MyException);
		const int16_t& GetAmount() const noexcept { return _amount; }

		void Increase(const int& amountP) throw(MyException);
		void Decrease(const int& amountP) throw(MyException);

		friend ostream& operator<<(std::ostream& out, const Dish& obj) {
			out << std::left;

			out << setw(30) << obj.dish->GetName() << SEPARATOR
				<< setw(10) << obj.dish->GetIngredientsCalories() << SEPARATOR
				<< setw(10) << obj.dish->GetPrice() << SEPARATOR
				<< setw(10) << obj._amount << SEPARATOR << endl;

			return out;
		}

	public:
		shared_ptr<Interface> dish;

	private:
		int16_t _amount;

	};
}
