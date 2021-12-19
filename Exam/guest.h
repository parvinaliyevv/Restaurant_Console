#pragma once
#include <iostream>
#include <ctime>

#include "restaurant.h"
#include "exceptions.h"
#include "dish.h"

using namespace std;
using namespace exceptions;
using namespace food;

class Guest {
	struct ClientHistory {
		string nameDish;
		string date;
		int amount;
		int price;

		friend ostream& operator<<(std::ostream& out, const ClientHistory& obj) {
			out << std::left;

			out << setw(30) << obj.nameDish << SEPARATOR
				<< setw(10) << obj.price << SEPARATOR
				<< setw(10) << obj.amount << SEPARATOR
				<< setw(25) << obj.date << SEPARATOR;

			return out;
		}
	};

public:
	explicit Guest(const string& fullnameP) { SetName(fullnameP); }
	Guest(const Guest& other) = delete;
	Guest& operator=(const Guest& other) = delete;

	void SetName(const string& fullnameP) throw(MyException);
	const string& GetName() const noexcept { return _fullname; }

	shared_ptr<Dish> GetOrder(const int& index) const noexcept;

	void NewOrder(Restaurant& restaurant) throw(MyException);
	void DelOrder(Restaurant& restaurant) throw(MyException);

	void AddIngredientOnDish(Restaurant& restaurant) throw(MyException);
	void DelIngredientOnDish(Restaurant& restaurant) throw(MyException);

	void ShowHistory(Restaurant& restaurant);
	void ShowBasket(Restaurant& restaurant);
	void InfoDish(Restaurant& restaurant);

	void SubmitBasket(Restaurant& restaurant) throw(MyException);

	bool SaveHistory(shared_ptr<Dish> data) const throw(MyException);
	vector<shared_ptr<ClientHistory>> LoadHistory() const throw(MyException);

private:
	string _fullname;
	list<shared_ptr<Dish>> _basket;

};
