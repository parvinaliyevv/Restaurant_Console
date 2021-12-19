#pragma once
#include <iostream>
#include <iomanip>

#include "product.h"
#include "exceptions.h"

using namespace std;
using namespace exceptions;

#define SEPARATOR " | "

namespace kitchen {
	class Provision {
	public:
		Provision(Product* productP, const int& quantityP) throw(MyException) : product(productP) { SetQuantity(quantityP); }

		void SetQuantity(const int& quantityP) throw(MyException);
		const uint16_t& GetQuantity() const noexcept { return _quantity; }

		void Increase(const int& quantityP) throw(MyException);
		void Decrease(const int& quantityP) throw(MyException);

		friend ostream& operator<<(std::ostream& out, const Provision& obj) {
			out << std::left;

			out << setw(30) << obj.product->GetName() << SEPARATOR
				<< setw(10) << obj.product->GetCalories() << SEPARATOR
				<< setw(10) << obj.product->GetPrice() << SEPARATOR
				<< setw(10) << obj._quantity << SEPARATOR << endl;

			return out;
		}

		friend class Stock;

	public:
		shared_ptr<Product> product;

	private:
		uint16_t _quantity;

	};
}
