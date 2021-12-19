#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <windows.h>

#include "stock.h"
#include "provision.h"
#include "functor.h"
#include "exceptions.h"

using namespace std;
using namespace kitchen;

namespace food {
	class Interface {
	public:
		Interface(const string& nameP, const int& priceP, const int& dishCategoryP);
		Interface& operator=(const Interface& other) = delete;
		virtual ~Interface() = 0 {}

		void SetName(const string& nameP) throw(MyException);
		void SetPrice(const int& priceP) throw(MyException);

		void IncreaseIngredient(const Provision productP, const int& quantityP) throw(MyException);
		void DecreaseIngredient(const Provision productP, const int& quantityP) throw(MyException);

		const string& GetName() const noexcept { return _name; }
		const uint32_t& GetPrice() const noexcept { return _price; }
		const uint16_t& GetDishCategory() const noexcept { return _dishCategory; }
		const vector<shared_ptr<Provision>>& GetIngredients() const noexcept { return _ingredients; }

		const Provision& GetIngredient(const int& indexP) const;
		size_t GetIngredientsCalories() const noexcept;

		void ShowIngredients() const noexcept;

		virtual void PrepareIngredients(const unique_ptr<Stock>& stock) throw(MyException);
		virtual bool SaveDish() const noexcept;
		virtual void Info() const noexcept;
		virtual void Cook() const noexcept;

		friend ostream& operator<<(std::ostream& out, const Interface& obj) {
			out << std::left;

			out << setw(30) << obj._name << SEPARATOR
				<< setw(10) << obj.GetIngredientsCalories() << SEPARATOR
				<< setw(10) << obj.GetPrice() << SEPARATOR << endl;

			return out;
		}

	protected:
		string _name;
		vector<shared_ptr<Provision>> _ingredients;
		uint32_t _price : 28;
		uint16_t _dishCategory : 5;

	};
}
