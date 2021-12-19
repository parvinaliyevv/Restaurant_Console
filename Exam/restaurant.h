#pragma once

#ifndef LIB 
#define LIB

#include <iostream>
#include <algorithm>
#include <ctime>
#include <list>

#include "dish.h"
#include "pizza.h"
#include "kebab.h"
#include "khangal.h"
#include "dolma.h"
#include "functor.h"
#include "exceptions.h"

using namespace std;
using namespace exceptions;
using namespace food;

enum { income = 1, cost };

#define SEPARATOR " | "

class Restaurant {
	struct RestaurantStatistics {
		int year;
		int month;
		int day;
		int money;

		bool operator==(const RestaurantStatistics& other) {
			return (this->year == other.year && this->month == other.month && this->day == other.day) ? true : false;
		}
		friend ostream& operator<<(std::ostream& out, const RestaurantStatistics& obj) {
			out << std::left;

			out << setw(10) << obj.year << SEPARATOR
				<< setw(10) << obj.month << SEPARATOR
				<< setw(10) << obj.day << SEPARATOR
				<< setw(10) << obj.money << SEPARATOR;

			return out;
		}
	};

public:
	Restaurant(const string& nameP);
	Restaurant(const Restaurant& restaurant) = delete;
	Restaurant& operator=(const Restaurant& restaurant) = delete;
	~Restaurant();

	void SetName(const string& nameP) throw(MyException);
	const string& GetName() const noexcept { return _name; }
	const uint64_t& GetMoney() const noexcept { return _safeDeposit; }

	void IncreaseMoney(const int& moneyP) throw(MyException);
	void DecreaseMoney(const int& moneyP) throw(MyException);

	bool CheckDish(shared_ptr<Interface> dish) const noexcept;
	Interface* CopyDish(const int& indexP) throw(MyException);

	shared_ptr<Interface> GetDish(const int& indexP) const noexcept;
	shared_ptr<Interface> GetDish(const string& nameP) const noexcept;

	void AddDish(const int& mealID) throw(MyException);
	void AddDish(const string& nameP, const int& priceP, const int& mealID, const vector<Provision>& ingredients) throw(MyException);
	void DelDish(const int& indexP) throw(MyException);

	void ShowMenu(const string& name = "guest") const noexcept;
	void ShowCategory() const noexcept;

	void CookDish(list<shared_ptr<Dish>>& _basket);

	void SaveDishs() const noexcept;
	bool LoadDishs() noexcept;

	void SaveSafeDeposit() const noexcept;
	void LoadSafeDeposit() noexcept;

	bool SaveStatistics(const int& money, const int& mode) const noexcept;
	vector<shared_ptr<RestaurantStatistics>> LoadStatistics() noexcept;

public:
	unique_ptr<Stock> _stock;

private:
	string _name;
	list<shared_ptr<Interface>> _dishs;
	list<string*> _category;
	uint64_t _safeDeposit;
};

#endif
